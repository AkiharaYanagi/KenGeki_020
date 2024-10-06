//=================================================================================================
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

		//カーソル
//		P_GrpBlink		m_cursor1p;
//		P_GrpBlink		m_cursor2p;

		//選択ID
//		CHARA_SELE_ID	m_chslct_id_1p { CHSLID_00 };	//現在位置1p
//		CHARA_SELE_ID	m_chslct_id_2p { CHSLID_02 };	//現在位置2p

		//プレイヤー毎位置
		P_ChSele_Pl		m_chsl_pl_1p;
		P_ChSele_Pl		m_chsl_pl_2p;

		//現在の選択状態を表示
		P_GrpBlink		m_state_1p;
		P_GrpBlink		m_state_2p;

		//フェード
		P_FadeRect		m_fade_toTitle;
		P_FadeRect		m_fade_toFighting;
//		bool			m_endWait { F };
		uint32			m_plus_wait { 0 };

		//モード保存
		MUTCH_MODE		m_mode { MODE_PLAYER_PLAYER };


		//ステージセレクト
		P_Grp			m_stageSelect;
		bool			m_stageDecide { F };

		//操作説明
		P_Grp			m_inst;

		//文字表示
		P_GrpBlink		m_txt_CharacterSelect;
		P_GrpBlink		m_txt_StageSelect;
		P_GrpBlink		m_txt_BGMSelect;

	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit ();
		void Load ();
		void Move ();

		P_GameScene Transit ();

	private:
		void Input ();
		STAGE_NAME GetStageName ();

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

#pragma endregion
	};


}	//namespace GAME


