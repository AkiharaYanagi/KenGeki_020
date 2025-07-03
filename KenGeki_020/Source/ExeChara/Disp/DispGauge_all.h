//=================================================================================================
//
// DispGauge_all ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/Param.h"
#include "DispGauge.h"
#include "DispAccel.h"
#include "../BtlParam.h"
#include "../../FtgMain/Ef/EfKouAtsu.h"

//#include "Chara.h"
//#include "../../FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispGauge_all : public TASK_VEC
	{
		//-----------------------------------------------------
		PLAYER_ID	m_playerID;			//プレイヤによる表示側
		P_Grp		m_gauge_all_bg;		//総合ゲージ背景

		P_Grp		m_life_value;		//体力
		P_Grp		m_stamina_value;	//剣撃
		P_Grp		m_hissatsu_value;	//必殺
		P_Grp		m_accel_value;		//アクセル

		P_Plgn		m_life_mask;		//ポリゴンマスク 体力
		P_Plgn		m_stamina_mask;		//ポリゴンマスク 剣撃
		P_Plgn		m_hissatsu_mask;		//ポリゴンマスク 必殺
		P_Plgn		m_accel_mask;		//ポリゴンマスク アクセル

		//-----------------------------------------------------
		enum DISP_FE_CONST
		{
			SIDE_1P = 0,
			SIDE_2P = 1,

			INPUT_PLAYER = 0,
			INPUT_CPU = 1,
		};


	public:
		DispGauge_all ();
		DispGauge_all ( const DispGauge_all & rhs ) = delete;
		~DispGauge_all ();

		void Load ();
		void ParamInit ( P_Param pParam );

		//プレイヤ別(1p,2p)のゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );

		//ゲージ類更新
		void UpdateGauge ( const BtlParam & btlPrm );

	private:

#pragma region CONST
		//定数

		static const VEC2 POS_FRAME_ALL_1P;		//全体枠
		static const VEC2 POS_FRAME_ALL_2P;
		static const VEC2 POS_LIFE_VALUE_1P;	//ライフ
		static const VEC2 POS_LIFE_VALUE_2P;
		static const VEC2 POS_STAMINA_VALUE_1P;	//スタミナ
		static const VEC2 POS_STAMINA_VALUE_2P;
		static const VEC2 POS_HISSATSU_VALUE_1P;	//必殺
		static const VEC2 POS_HISSATSU_VALUE_2P;
		static const VEC2 POS_ACCEL_VALUE_1P;	//アクセル
		static const VEC2 POS_ACCEL_VALUE_2P;

#pragma endregion

	};

	using P_DispGauge_all = std::shared_ptr < DispGauge_all >;


}	//namespace GAME

