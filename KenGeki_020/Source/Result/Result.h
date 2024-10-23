//=================================================================================================
//
//	リザルト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "ResultMenu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Result : public Scene, public std::enable_shared_from_this < Result >
	{
		P_GrpMovie		m_mov;		//背景ムービー

		P_Grp			m_chara;	//キャラ画像
		P_Grp			m_state;	//ステート(数値群)
		P_Grp			m_MsgWnd;	//メッセージウィンドウ
		P_Grp			m_inst;		//操作説明

		float			m_chara_x { 0 };		//キャラ表示位置
		float			m_chara_vx { 0 };		//キャラ表示速度

		P_FadeRect		m_fade_in;
		P_FadeRect		m_fade_out;
		uint32			m_plus_wait { 0 };

		P_GrpBlink		m_next_tri;		//次へ表示

		//メニュ
//		P_ResultMenu	m_menu;

		//勝利メッセージ
		P_GrpStr		m_win_msg;
		s3d::String		m_msg;
		UINT			m_time_count { 0 };

		s3d::HashTable < CHARA_NAME, s3d::String >  m_ch_msg;


		//数値
		P_GrpStr		m_n_offset;
		P_GrpStr		m_n_max_chn;
		P_GrpStr		m_n_max_dmg;

	public:
		Result ();
		Result ( const Result & rhs ) = delete;
		~Result ();

		void Init ();
		void Load ();
		void ParamInit ();

		void Move ();

		P_GameScene Transit ();

	private:

		P_GrpStr MakeStr ( float x, float y );

#pragma region CONST

		//キャラ位置
		static const float CHARA_PY;	//位置Y

		static const float CHARA_PX;	//目標位置
		static const float CHARA_SX;	//初期位置
		static const float CHARA_VX;	//速度

		//他位置
		static const float NEXT_X;	//次に移行を促す　▼
		static const float NEXT_Y;

		static const float NUM_BG_X;	//戦闘数値 背景
		static const float NUM_BG_Y;	
		static const float NUM_X;	//戦闘数値
		static const float NUM_Y;
		static const float NUM_P;

		static const float MSG_WND_X;	//勝利メッセージウィンドウ
		static const float MSG_WND_Y;

		static const float MSG_X;	//勝利メッセージ
		static const float MSG_Y;

		static const float INST_X;	//操作説明
		static const float INST_Y;
#pragma endregion
	};

	using P_Result = std::shared_ptr < Result >;


}	//namespace GAME

