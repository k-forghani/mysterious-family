#include "crow.h"
#include "libs/sha256.h"
#include "libs/sft.h"

using namespace std;

// SFT sft(true);
SFT sft;

int main() {
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

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/view")([](){
        crow::mustache::context ctx;
        ctx["data"] = sft.toJSON();
        auto page = crow::mustache::load("view.html");
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/explore")([](){
        crow::mustache::context ctx;
        auto page = crow::mustache::load("explore.html");
        return page.render(ctx);
    });

    CROW_ROUTE(app, "/request/<string>")
    .methods("POST"_method)
    ([](const crow::request& req, const string& operation){
        auto body = crow::json::load(req.body);
        
        crow::json::wvalue response({{"status", "success"}});

        if (!body) {
            response["status"] = "failure";
            return response;
        }

        if (operation == "add-person") {

            string id = body["id"].s();
            string fatherID = body["fatherID"].s();
            string motherID = body["motherID"].s();
            string name = body["name"].s();

            string newID = sft.addPerson(id, fatherID, motherID, name);

            response["newID"] = newID;

        }
        else if (operation == "find-person") {

            string id = body["id"].s();

            bool result = sft.findPerson(id);

            response["result"] = result;

        } else if (operation == "delete-person") {

            string id = body["id"].s();

            sft.deletePerson(id);

        } else if (operation == "is-ancestor") {

            string ancestor = body["ancestor"].s();
            string child = body["child"].s();

            bool result = sft.isAncestor(ancestor, child);

            response["result"] = result;

        } else if (operation == "are-siblings") {

            string firstPerson = body["firstPerson"].s();
            string secondPerson = body["secondPerson"].s();

            bool result = sft.areSiblings(firstPerson, secondPerson);

            response["result"] = result;

        } else if (operation == "have-extended-relationship") {

            string firstPerson = body["person1"].s();
            string secondPerson = body["person2"].s();

            bool result = sft.haveExtendedRelationship(firstPerson, secondPerson);

            response["result"] = result;

        } else if (operation == "get-lowest-common-ancestor") {

            string firstPerson = body["person1"].s();
            string secondPerson = body["person2"].s();

            string lca = sft.getLowsetCommonAncestor(firstPerson, secondPerson);

            response["lca"] = lca;

        } else if (operation == "get-most-distance-from-children") {

            string id = body["person"].s();

            int mostDistance = sft.getMostDistanceFromChildren(id);

            response["most_distance"] = mostDistance;

        } else if (operation == "get-longest-relationship") {

            auto relationship = sft.getLongestRelationship();

            response["most_distance"] = {{"first_person", relationship.first}, {"second_person", relationship.second}};

        } else {
            response["status"] = "failure";
        }

        return response;
    });

    app.bindaddr("127.0.0.1").port(8000).multithreaded().run();
}