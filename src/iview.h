#ifndef IVIEW_H
#define IVIEW_H

#include <string>
#include <cstdint>
#include <ctime>
#include <vector>

using string = std::wstring;
using str_array =  std::vector<string>;

class IView
{
public:
    enum class GAME_LAYOUT
    {
        MAIN_MENU,/*shows main menu*/
		LOBBY,/*shows lobby*/
		JOIN_GAME,/*shows list of available local hosts and edit for remote host address*/
		SAVE_GAME,/*list of saves or new save*/
		LOAD_GAME,/*show list of available saves*/
		GAME
    };

	enum class GAME_MODE {
		MODE_PENTAGO, 		/* 6x6 board, 4 quadrants*/
		MODE_PENTAGO_XL 	/* 9x9 board, 9 quadrants*/
	};
	
    enum class QUADRANT{	
		III=2,	II=1,	IX=9,
		IV=3,	I=4,	VIII=8,
		V=5, 	VI=6,	VII=7	};/* do not ask, just look at the position in the enum... */

	enum class DIRECTION{LEFT, RIGHT};      /*  for quadrant rotation   */

 	enum class MESSAGE_TYPE{INFO, WARNING, ERROR, TIP};
	
	enum class MESSAGE_BUTTONS {
		OK,
		YES_NO,
		YES_NO_CANCEL,
		NO_BUTTONS /*no buttons*/
	};
	
	enum class MESSAGE_ICON {
		NONE,
		INFO,
		WORNING,
		ERROR,
		WAITING/*some circle or whatever*/
	};
	
	enum class MESSAGE_ANSWER {
		OK,
		YES,
		NO,
		CANCEL
	};
	
	enum class LOBBY_STATUS {
		NORMAL, /*lobby just created*/
		READY /*player ready to start and waiting for others*/
	};
	
public:

	virtual void Enable_chat()=0; //only while game or lobby
	virtual void Disable_chat()=0; //only while game or lobby
	
	virtual void Set_game_layout(GAME_LAYOUT layout)=0; /*set the current view mode*/
	
	virtual void Set_lobby_params(LOBBY_STATUS status, const string& lobby_name = L"", int player_count=-1)=0;
	//lobby_name = L"" --- do not change
	//player_count < 0 --- do not change
	virtual void Set_lobby_player_name(int player_num, const string& name)=0;
	virtual void Set_lobby_player_color(int player_num, int rgb)=0;
	virtual void Set_lobby_player_color_charge_enable(int player_num, bool enabled)=0;
	virtual void Set_lobby_player_avatar(int player_num, const char* image)=0;
	//image can be as any format, like readed from the file (BMP,PNG,JPG)
	
	virtual void Set_hosts_list(const str_array& hosts)=0;
    
	virtual void Clear_board()=0;/*remove all the stones*/
	virtual void Put_stone(int row, int col, int grb)=0; /*put stone at [row, col] with color as rgb*/
    virtual void Rotate_quadrant(QUADRANT quadrant, TURN turn)=0; //rotate selected quadrant to specified direction
	
	virtual void Disable_rotate_quadrant()=0;
	virtual void Enable_rotate_quadrant()=0;
	
	virtual void Show_quick_message(string text, MESSAGE_TYPE type = MESSAGE_TYPE::INFO, int mili_sec=0)=0; /*show some text to player during the game*/
	//mili_sec - time how long it should be displayed. If 0 - until the next message
	virtual void Show_message(string text, MESSAGE_BUTTONS buttons = MESSAGE_BUTTONS::OK, MESSAGE_ICON icon=MESSAGE_ICON::NONE)=0; 
	/*show some text to player during the game*/
	virtual void Hide_message()=0;/*ti hide current message*/
	
	virtual void Clear_chat()=0;
	virtual void Add_message_to_chat(string from, string text, time_t message_time)=0;
public:
    virtual void Request_show_lobby(int player_count)=0;//for local game only
	virtual void Request_lobby_ready()=0;//start game for local and "ready" for network game
    virtual void Request_leave_lobby()=0;
	
	virtual void Request_get_saves_list()=0;
	virtual void Request_save_game(const string& save_name)=0;
    virtual void Request_load_game(const string& save_name)=0;
	
	virtual void Request_get_hosts_list()=0;
	virtual void Request_join_game(const string& host_address)=0;
	virtual void Request_host_game(const string& lobby_name, int player_count, const string& password = L"")=0;
    
	virtual void Request_put_stone(int row, int col)=0;
    virtual void Request_rotate_quadrant(QUADRANT quadrant, DIRECTION direction)=0;
	
	virtual void Request_send_to_chat(const string& message)=0;
	
	virtual void Request_answer_massage(MESSAGE_ANSWER answer)=0;
	
    virtual void Request_leave_game()=0;
};

#endif // IVIEW_H