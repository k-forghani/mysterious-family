#include "crow.h"
#include "libs/sha256.h"
#include "libs/sft.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/explore")([](){
        SFT sft(true);
        sft.addPerson("1");
        sft.addPerson("2");
        sft.addPerson("121", "1", "2");
        sft.addPerson("122", "1", "2");
        sft.addPerson("123", "1", "2");
        sft.addPerson("3");
        sft.addPerson("4");
        sft.addPerson("341", "3", "4");
        sft.addPerson("1213411", "121", "341");
        sft.addPerson("5");
        sft.addPerson("6");
        sft.addPerson("561", "5", "6");
        sft.addPerson("1235611", "123", "561");

        crow::mustache::context ctx;
        ctx["data"] = sft.toJSON();
        auto page = crow::mustache::load("explore.html");
        return page.render(ctx);
    });

    app.bindaddr("127.0.0.1").port(8000).multithreaded().run();
}