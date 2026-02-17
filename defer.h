#pragma once

#include <utility>

struct __deferrer {
  template <typename F>
  auto operator<<(F&& f) {
    return Defer<F>(std::forward<F>(f));
  }

  template <typename F>
  struct Defer final {
    F func;
    Defer(F&& f) : func(std::forward<F>(f)) {}
    Defer(const Defer&) = delete;
    Defer(Defer&&) = delete;
    ~Defer() { func(); }
    Defer& operator=(const Defer&) = delete;
    Defer& operator=(Defer&&) = delete;
  };
};

#define __defer_concat(x, y) x##y
#define __defer_var_gen(y) __defer_concat(__defer_var, y)
#define defer auto __defer_var_gen(__COUNTER__) = __deferrer{} << [&]
