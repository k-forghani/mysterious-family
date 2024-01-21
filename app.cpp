#include "crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        return page.render(ctx);
    });

    app.bindaddr("127.0.0.1").port(8000).multithreaded().run();
}