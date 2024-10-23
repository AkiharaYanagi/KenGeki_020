﻿//=================================================================================================
//
//	CharaSele ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgMain/FtgConst.h"	
#include "../GameMain/Scene.h"
#include "CharaSeleConst.h"
#include "CharaSele_Player.h"
#include "../GameMain/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaSele : public Scene, public std::enable_shared_from_this < CharaSele >
	{
		//BG
		P_Grp			m_bg;

		//Scroll
		P_Grp			m_scroll;
		float			m_scrl_y { 0 };
		P_Grp			m_scroll_Stage;
		float			m_scrlStg_x { 0 };

		//CharaFace
		P_Grp			m_charaFace;

		//プレイヤー毎位置
		P_ChSele_Pl		m_chsl_pl_1p;
		P_ChSele_Pl		m_chsl_pl_2p;


		//現在の選択状態を表示
		P_GrpBlink		m_state_1p;
		P_Grp			m_state_bar_1p;
		P_GrpBlink		m_state_2p;
		P_Grp			m_state_bar_2p;

		//フェード
		P_FadeRect		m_fade_toTitle;
		P_FadeRect		m_fade_toFighting;
//		bool			m_endWait { F };
		uint32			m_plus_wait { 0 };

		//モード保存
		MUTCH_MODE		m_mode { MODE_PLAYER_PLAYER };

		//文字表示
		P_GrpBlink		m_txt_CharacterSelect;

		//ステージセレクト
		P_GrpBlink		m_txt_StageSelect;
		P_Grp			m_stageSelect;
		bool			m_stageDecide { F };
		P_GrpBlink		m_stageSelectTri;

		//BGMセレクト
		P_GrpBlink		m_txt_BGMSelect;
		P_Grp			m_bgmSelect;
		
		//操作説明
		P_Grp			m_inst;


	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit ();
		void Load ();
		void Move ();

		P_GameScene Transit ();

		void Save ();

	private:
		void Input ();
		STAGE_NAME GetStageName ();
		void AssignStage ( STAGE_NAME name );

#pragma region CONST

		//位置
		static const float TXT_CHSL_X;
		static const float TXT_CHSL_Y;
		static const float TXT_STSL_X;
		static const float TXT_STSL_Y;
		static const float TXT_BGM_X;
		static const float TXT_BGM_Y;
		static const float TXT_INST_X;
		static const float TXT_INST_Y;

		static const float CH_STT_X_1P;
		static const float CH_STT_X_2P;
		static const float CH_STT_Y;
		static const float CH_BAR_X_1P;
		static const float CH_BAR_X_2P;
		static const float CH_BAR_Y;

		static const float STG_X;
		static const float STG_Y;
		static const float STG_BG_X;
		static const float STG_BG_Y;
		static const float STG_TRI_X;
		static const float STG_TRI_Y;

		static const float BGM_X;
		static const float BGM_Y;
		static const float BGM_TRI_X;
		static const float BGM_TRI_Y;

		static const float INST_X;
		static const float INST_Y;

#pragma endregion
	};


}	//namespace GAME


