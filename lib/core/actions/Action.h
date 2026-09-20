#pragma once

struct Robot;

struct Action {
  virtual ~Action() = default;
  virtual void run(Robot &r) = 0;
  virtual void end(Robot &r) {}
  virtual void cancel() { canceled = true; }
  virtual bool completed() const { return canceled; }

protected:
  bool canceled = false;
};
