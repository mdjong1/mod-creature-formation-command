#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "Configuration/Config.h"

string sqlDefault = "DEFAULT";
char *defaultEntry = const_cast<char *>(sqlDefault.c_str());

class CreatureFormationsCommand : public CommandScript{
public:

    CreatureFormationsCommand() : CommandScript("CreatureFormationsCommand") {}

    [[nodiscard]] std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> packCommandTable =
                {
                        {"create", SEC_GAMEMASTER, false, &CreateCreatureFormation, ".pack create leaderGUID* memberGUID* groupAI dist angle"},
                        {"disband", SEC_GAMEMASTER, false, &DisbandCreatureFormation, ".pack disband leaderGUID*"},
                };

        static std::vector<ChatCommand> commandTable =
                {
                        {"pack", SEC_GAMEMASTER, false, nullptr, "",  packCommandTable},
                };

        return commandTable;
    }

    static bool CreateCreatureFormation(ChatHandler *handler, char const *args) {
        // .pack create leadGUID* memGUID* groupAI dist angle
        handler->PSendSysMessage(args);

        if (!*args) {
            handler->PSendSysMessage("[CreatureFormations] No arguments provided to create a pack with!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* leaderGuid = strtok((char*)args, " ");
        if (!leaderGuid) {
            handler->PSendSysMessage("[CreatureFormations] Missing leader GUID");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* memberGuid = strtok(nullptr, " ");
        if (!memberGuid) {
            handler->PSendSysMessage("[CreatureFormations] Missing member GUID");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* groupAi = strtok(nullptr, " ");
        if (!groupAi)
            groupAi = defaultEntry;

        char* dist = strtok(nullptr, " ");
        if (!dist)
            dist = defaultEntry;

        char* angle = strtok(nullptr, " ");
        if (!angle)
            angle = defaultEntry;

        WorldDatabase.PQuery("INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES(%s, %s, %s, %s, %s)", leaderGuid, memberGuid, dist, angle, groupAi);

        return true;
    }

    static bool DisbandCreatureFormation(ChatHandler *handler, char const *args) {
        if (!args) {
            handler->PSendSysMessage("[CreatureFormations] No arguments provided to create a pack with!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* leaderGuid = strtok((char*)args, " ");
        if (!leaderGuid) {
            handler->PSendSysMessage("[CreatureFormations] Missing leader GUID");
            handler->SetSentErrorMessage(true);
            return false;
        }

        WorldDatabase.PQuery("DELETE FROM `creature_formations` WHERE `leaderGUID` = %s", leaderGuid);

        return true;
    }
};

void AddCreatureFormationsCommand() {
    new CreatureFormationsCommand();
}

