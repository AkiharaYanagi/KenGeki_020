﻿//=================================================================================================
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
		P_Grp		m_menu;
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
			TITLE_TO_BATTLE,
			TITLE_TO_TRAINING,
		};

		TITLE_TO	m_to { TITLE_TO_BATTLE };

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

#pragma region CONST

		static const float BG_X;	//BG
		static const float BG_Y;
		static const float BG_VX;	//速度
		static const float BG_P;	//切り替えポイント

		static const float LOGO_X;	//ロゴ
		static const float LOGO_Y;

		static const float MENU_X;	//メニュ
		static const float MENU_Y;

		static const float CURSOR_X;	//カーソル
		static const float CURSOR_Y;
		static const float CURSOR_P;	//移動ピッチ

		static const float INST_X;	//操作説明
		static const float INST_Y;

		static const uint32 FADE_IN_T;	//フェード時間
		static const uint32 FADE_OUT_T;	//フェード時間

		static const uint32 TITLE_CALL_WAIT;	//タイトルコールウェイト

#pragma endregion

	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

