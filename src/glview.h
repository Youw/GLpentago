#ifndef GLVIEW_H
#define GLVIEW_H

#include <QObject>

#include "iview.h"

class GLview :  public QObject, public IView
{
  Q_OBJECT
  class GLviewImpl;
  GLviewImpl *impl;//everithing is here
public:

    GLview();

    GLview(GLview&& right);

    GLview& operator=(GLview&&right);

    GLview(const GLview&) = delete;//can not be copied
    GLview& operator=(const GLview&) = delete;//can not be copied

    ~GLview();

//    IView: (see iview.h)
public: //some kind of slots
    virtual void Show_game_ended(WINNER winner, const string& winner_name);

    virtual void Set_saves_list(const str_array& save_names,const str_array& saves_info) override;

    virtual void Enable_chat() override;
    virtual void Disable_chat() override;

    virtual void Set_game_layout(GAME_LAYOUT layout) override;

    virtual void Set_lobby_params(LOBBY_STATUS status, const string& lobby_name = L"", int player_count=-1) override;
    virtual void Set_lobby_player_name(int player_num, const string& name) override;
    virtual void Set_lobby_player_color(int player_num, uint32_t rgb) override;
    virtual void Set_lobby_player_color_charge_enable(int player_num, bool enabled) override;
    virtual void Set_lobby_player_avatar(int player_num, const char* image) override;


    virtual void Set_hosts_list(const str_array& hosts) override;

    virtual void Clear_board() override;
    virtual void Put_stone(int row, int col, uint32_t rgb) override;
    virtual void Rotate_quadrant(QUADRANT quadrant, DIRECTION direction) override;

    virtual void Disable_rotate_quadrant() override;
    virtual void Enable_rotate_quadrant() override;

    virtual void Show_quick_message(string text, MESSAGE_TYPE type = MESSAGE_TYPE::M_INFO, int mili_sec=0) override; /*show some text to player during the game*/

    virtual void Show_message(string text, MESSAGE_BUTTONS buttons = MESSAGE_BUTTONS::OK, MESSAGE_ICON icon=MESSAGE_ICON::I_NONE) override;

    virtual void Hide_message() override;

    virtual void Ask_user_text_input(const string& question, USER_INPUT_BUTTON_NAME button_accept_text) override;

    virtual void Clear_chat() override;
    virtual void Add_message_to_chat(string from, string text, time_t message_time) override;

public://signals to presenter
    virtual void Request_enter_game_layout(GAME_LAYOUT layout) override;

    virtual void Request_show_lobby(int player_count) override;
    virtual void Request_lobby_ready() override;
    virtual void Request_leave_lobby() override;

    virtual void Request_get_saves_list() override;
    virtual void Request_save_game(const string& save_name) override;
    virtual void Request_load_game(const string& save_name) override;

    virtual void Request_get_hosts_list() override;
    virtual void Request_join_game(const string& host_address) override;
    virtual void Request_host_game(const string& lobby_name, int player_count, const string& password = L"") override;

    virtual void Request_put_stone(int row, int col) override;
    virtual void Request_rotate_quadrant(QUADRANT quadrant, DIRECTION direction) override;

    virtual void Request_send_to_chat(const string& message) override;

    virtual void Request_massage_answer(MESSAGE_ANSWER answer) override;

    virtual void Request_user_text_output(bool accepted, const string& text) override;

    virtual void Request_leave_game() override;

    virtual void Requset_change_ivew_to_next() override;
};

#endif // GLVIEW_H
