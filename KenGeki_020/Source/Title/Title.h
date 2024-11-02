//=================================================================================================
//
//	タイトル イントロダクション対応
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Title : public Scene, public std::enable_shared_from_this < Title >
	{
		P_Grp		m_bg;
		float		m_bg_x { 0 };

		P_Grp		m_logo;
		P_Grp		m_menu_1PvsCPU;
		P_Grp		m_menu_1Pvs2P;
		P_Grp		m_menu_CPUvsCPU;
		P_Grp		m_menu_Training;
		P_Grp		m_cursor;
		P_Grp		m_inst;		//操作説明

		P_FadeRect	m_fade_in;
		P_FadeRect	m_fade_out;
		uint32		m_plus_wait { 0 };

		float		m_cursor_scaling_vy { 0.05f };
		float		m_cursor_scaling_y { 1.f };

		P_Timer		m_tmr_title_bgm;
		P_Timer		m_tmr_title_call;

		//シーン選択
		enum TITLE_TO
		{
			TITLE_TO_BATTLE_1PvsCPU,
			TITLE_TO_BATTLE_1Pvs2P,
			TITLE_TO_BATTLE_CPUvsCPU,
//			TITLE_TO_BATTLE,
			TITLE_TO_TRAINING,
		};

		TITLE_TO	m_to { TITLE_TO_BATTLE_1PvsCPU };

		//デモモード
		bool		m_bDemo { F };
		P_GrpStr	m_strDemo;	//デモ表示 "- Demo Mode -"文字列
		P_GrpStr	m_strDemoSwitch;	//デモ操作切換 "F9で切換" 文字列
		P_PrmRect	m_barDemo;	//時間表示バー
		Timer		m_tmrDemo;	//タイマ
		P_FadeRect	m_fade_demo;		

		//Ver.
		P_GrpStr	m_strVer;


	public:
		Title ();
		Title ( const Title & rhs ) = delete;
		~Title ();

		void ParamInit ();

		void Move ();
		void Load ();

		P_GameScene Transit ();

	private:
		void Input ();

		void ValidDemo ( bool b );
		void OnDemo ();
		void OffDemo ();

		CHARA_NAME GetCharaName_Rnd ();
		STAGE_NAME GetStageName_Rnd ();
		BGM_ID GetBGM_ID_Rnd ();

#pragma region CONST

		static const float BG_X;	//BG
		static const float BG_Y;
		static const float BG_VX;	//速度
		static const float BG_P;	//切り替えポイント

		static const float LOGO_X;	//ロゴ
		static const float LOGO_Y;

		static const float MENU_X;	//メニュ
		static const float MENU_Y;
		static const float MENU_Y0;
		static const float MENU_Y1;
		static const float MENU_Y2;
		static const float MENU_Y3;

		static const float CURSOR_X;	//カーソル
		static const float CURSOR_Y;
		static const float CURSOR_P;	//移動ピッチ

		static const float INST_X;	//操作説明
		static const float INST_Y;

		static const uint32 FADE_IN_T;	//フェード時間
		static const uint32 FADE_OUT_T;	//フェード時間

		static const uint32 TITLE_CALL_WAIT;	//タイトルコールウェイト

		static const int32 WAIT_DEMO;	//待機時間
		static const int32 BAR_DEMO_Y;	//バー表示Y
#pragma endregion

	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

