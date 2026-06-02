#include "core/Game.hpp"
#include "raylib.h"

namespace game {
    namespace core {

        bool Game::init(int width, int height, const std::string& title, int targetFPS) {
            m_width = width;
            m_height = height;

            // Initialize raylib window
            InitWindow(width, height, title.c_str());

            // Set target FPS
            SetTargetFPS(targetFPS);

            m_running = true;

            // Initialize all components
            for (auto& model : m_models) {
                if (model->isActive()) {
                    model->init();
                }
            }

            for (auto& view : m_views) {
                if (view->isActive()) {
                    view->init();
                }
            }

            for (auto& controller : m_controllers) {
                if (controller->isActive()) {
                    controller->init();
                }
            }

            return true;
        }

        void Game::run() {
            while (!WindowShouldClose() && m_running) {
                // Calculate delta time
                m_deltaTime = GetFrameTime();

                // Update game state
                update();

                // Render frame
                render();
            }
        }

        void Game::shutdown() {
            // Clear all components
            m_models.clear();
            m_views.clear();
            m_controllers.clear();

            // Close raylib window
            CloseWindow();

            m_running = false;
        }

        void Game::update() {
            // Handle input through controllers
            for (auto& controller : m_controllers) {
                if (controller->isActive()) {
                    controller->handleInput();
                    controller->update(m_deltaTime);
                }
            }

            // Update models
            for (auto& model : m_models) {
                if (model->isActive()) {
                    model->update(m_deltaTime);
                }
            }

            // Update views (for animations, etc.)
            for (auto& view : m_views) {
                if (view->isActive()) {
                    view->update(m_deltaTime);
                }
            }
        }

        void Game::render() {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Render all views
            for (auto& view : m_views) {
                if (view->isActive()) {
                    view->render();
                }
            }

            EndDrawing();
        }

        void Game::addModel(std::shared_ptr<models::Model> model) {
            m_models.push_back(model);
        }

        void Game::addView(std::shared_ptr<views::View> view) {
            m_views.push_back(view);
        }

        void Game::addController(std::shared_ptr<controllers::Controller> controller) {
            m_controllers.push_back(controller);
        }

    } // namespace core
} // namespace game
