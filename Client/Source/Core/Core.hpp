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
#include "../Hud/Left/HudLeft.hpp"
#include "../Hud/Right/HudRight.hpp"
#include "../Particle/ParticleSystem.hpp"
#include "../Model3D/Model3D.hpp"
#include "../Map/Resources/IResources.hpp"
#include "../Map/Resources/AResources.hpp"

namespace Zappy {

    struct Cloud {
        Vector3 position;
        Vector3 size;
        Color color;
        Vector3 speed;
    };

    class Core {
        public:
            Core(const std::string& host, int port);
            ~Core();

            void run();
            void handleServerMessages();

        protected:
            std::unique_ptr<Api> _api;
            std::unique_ptr<Map> _map;
            std::unique_ptr<ParticleSystem> _particleSystem;
            std::thread _networkThread;
            bool _running;
            bool _debug;
            HudLeft _hudLeft;
            HudRight _hudRight;

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

            void stop();
            void adjustTimeUnit(int value);

            void _initClouds(int count);
            void _drawClouds(const std::vector<Cloud>& clouds);
            void _moveClouds(std::vector<Cloud>& clouds, float deltaTime);
            void _setCloudsPosition();

            std::vector<Cloud> _clouds;
    };

}

#endif /* !CORE_HPP_ */
