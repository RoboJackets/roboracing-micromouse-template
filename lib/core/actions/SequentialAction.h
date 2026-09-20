#pragma once
#include "Action.h"
#include <memory>
#include <vector>
struct SequentialAction : Action {
  std::vector<std::unique_ptr<Action>> actions{};
  size_t index = 0;
  SequentialAction() = default;
  SequentialAction(std::vector<std::unique_ptr<Action>> actions)
      : actions(std::move(actions)) {}

  template <typename... Args> static SequentialAction make(Args &&...args) {
    std::vector<std::unique_ptr<Action>> v;
    (v.push_back(
         std::make_unique<std::decay_t<Args>>(std::forward<Args>(args))),
     ...);
    return SequentialAction(std::move(v));
  }

  void run(Robot &r) override {
    while (index < actions.size() && actions[index]->completed()) {
      actions[index]->end(r);
      index++;
    }

    if (index >= actions.size()) {
      canceled = true;
      return;
    }

    actions[index]->run(r);
  }
  void end(Robot &r) override {
    if (index < actions.size())
      actions[index]->end(r);
  }
  void cancel() override {
    canceled = true;
    if (index < actions.size())
      actions[index]->cancel();
  }
};
