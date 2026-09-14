#pragma once

#include <memory>

#include "recomp/app/game_recomp_app.h"

class FightNightChampionApp final : public recomp::GameRecompApp {
 public:
  static std::unique_ptr<rex::ui::WindowedApp> Create(rex::ui::WindowedAppContext& context) {
    return std::unique_ptr<FightNightChampionApp>(new FightNightChampionApp(context));
  }

 private:
  explicit FightNightChampionApp(rex::ui::WindowedAppContext& context)
      : GameRecompApp(context, Descriptor(), PPCImageConfig) {}

  static recomp::GameDescriptor Descriptor() {
    recomp::GameDescriptor descriptor;
    descriptor.app_name = "fight_night_champion";
    descriptor.display_name = "Fight Night Champion";
#ifdef RECOMP_DEVELOPMENT_GAME_ROOT
    descriptor.development_game_root = RECOMP_DEVELOPMENT_GAME_ROOT;
#endif
    return descriptor;
  }
};
