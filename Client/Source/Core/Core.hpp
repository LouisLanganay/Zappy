/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_


#include <string>
#include <thread>
#include <atomic>
#include <memory>

#include "../API/Api.hpp"
#include "../Map/Map.hpp"
#include "../API/Events.h"
#include "../Hud/Hud.hpp"

namespace Zappy {
    class Core {
        public:
            Core(const std::string& host, int port);
            ~Core();

            void run();
            void handleServerMessages();

        protected:
            std::unique_ptr<Api> _api;
            std::unique_ptr<Map> _map;
            std::thread _networkThread;
            bool _running;
            bool _debug;
            Hud _hud;

            void msz(std::string message);
            void bct(std::string message);
            void tna(std::string message);
            void pnw(std::string message);
            void ppo(std::string message);
            void plv(std::string message);
            void pin(std::string message);
            void pex(std::string message);
            void pbc(std::string message);
            void pic(std::string message);
            void pie(std::string message);
            void pfk(std::string message);
            void pdr(std::string message);
            void pgt(std::string message);
            void pdi(std::string message);
            void enw(std::string message);
            void ebo(std::string message);
            void edi(std::string message);
            void sgt(std::string message);
            void sst(std::string message);
            void seg(std::string message);
            void smg(std::string message);
            void suc();
            void sbp();
    };

}

#endif /* !CORE_HPP_ */
