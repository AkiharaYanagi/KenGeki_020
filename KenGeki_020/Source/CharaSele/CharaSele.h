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

		//カーソル
		P_GrpBlink		m_cursor1p;
		P_GrpBlink		m_cursor2p;

		CHARA_SELE_ID	m_chslct_id_1p { CHSLID_00 };	//現在位置1p
		CHARA_SELE_ID	m_chslct_id_2p { CHSLID_02 };	//現在位置2p

#if 0
		//キャラ枠位置
		std::vector < ChSlct >		mv_pos;


		//キャラ立絵
		P_GrpAcv		m_chara_1p;
		P_GrpAcv		m_chara_2p;

		//選択キャラ名(パラメータ)
		CHARA_NAME		m_charaName1p { CHARA_OUKA };	//１Pキャラ名
		CHARA_NAME		m_charaName2p { CHARA_OUKA };	//２Pキャラ名

		bool m_bDecide1p { F };	//1P側決定(1Pコントローラで2P側を操作)
		bool m_bDecide2p { F };	//2P側決定

		P_FadeRect		m_fade;
		bool			m_endWait { F };

		//モード保存
		MUTCH_MODE		m_mode { MODE_PLAYER_PLAYER };

#endif // 0

		P_ChSele_Pl		m_chsl_pl_1p;
		P_ChSele_Pl		m_chsl_pl_2p;

#if 0
		P_PrmRect		m_fade_out;
		UINT			m_wait_out_title { 0 };
		UINT			m_wait_out_fighting { 0 };
#endif // 0

		//ステージセレクト
		P_Grp			m_stageSelect;
		bool			m_stageDecide { F };

	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
		STAGE_NAME GetStageName ();
	};


}	//namespace GAME


