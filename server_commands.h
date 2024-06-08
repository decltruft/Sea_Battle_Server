#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

enum class Reguests
{
    REQ_REG,
    REQ_REC,
    REQ_ENT,

    REQ_SETT,
    REQ_COMMUN,
    REQ_GAME,
    REQ_EXIT,
    REQ_FIGHT
};

enum class Registration_Commands
{
    FREE_UNAME,
    FREE_EMAIL,

    NOT_VALIED_UNAME,
    NOT_VALIED_ENAIL,

    REG_CONFIRM
};

enum class Recover_Commands
{
    NOT_CORRECTED_MATCH,

    RECOV_CONFIRM
};

enum class Entrance_Commands
{
    NOT_EXISTED_UNAME,
    NOT_CORRECTED_PASSWORD,

    AGREE_TO_LOGIN
};

enum class Settings_Commands
{
    CHANGE_UNAME,
    CHANGE_EMAIL,
    CHANGE_PASSWORD,

    DELETE_ACCOUNT,

    NOT_VALIED_UNAME,
    NOT_VALIED_EMAIL,

    UNAME_HB_CHANGED,
    EMAIL_HD_CHANGED,
    PASSWORD_HB_CHANGED,

    ACCOUNT_HB_DELETED
};

enum class G_Preparing_Commands
{
    REFRESH,

    CREAT_CONNECTION,
    CONNECT_GAME,

    STOP_CONNECTION,
    DENIED_TO_CONNECTION,

    ACCEPT_CONNECTION
};

enum class G_Process_Commands
{
    YOURE_WON,
    YOURE_LOSE,

    SHOT,
    HIT,
    MISSED,

    GET_READY,
    NOT_READY,

    SET_RANDOM_PLACES,
    RESET_SHIPS,

    SET_SHIP,
    NOT_ALLOWED,

    START_FIGHT,
    LEAVE_FIGHT,

    OPP_HAS_LEFT
};

enum class Ship_Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

#endif // SERVER_COMMANDS_H
