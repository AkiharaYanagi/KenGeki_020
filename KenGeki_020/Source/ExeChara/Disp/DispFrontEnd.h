//=================================================================================================
//
// DispFrontEnd ヘッダファイル
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

//#include "Chara.h"
//#include "../../FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispFrontEnd : public TASK_VEC
	{
		//-----------------------------------------------------
		PLAYER_ID	m_playerID;			//プレイヤによる表示側

		//-----------------------------------------------------
		P_DispGauge	m_gaugeLife;		//ライフゲージ
		P_DispGauge	m_gaugeBalance;		//バランスゲージ
		P_DispGauge	m_gaugeMana;		//マナゲージ

#if	0
		P_DispAccel	m_gaugeAccel;		//アクセルゲージ
		PrmRect		m_gaugeHitStop;			//ヒットストップ時間表示
		PrmRect		m_gaugeLurch;			//のけぞり時間表示
#endif	//0

		//-----------------------------------------------------

		enum DISP_FE_CONST
		{
			SIDE_1P = 0,
			SIDE_2P = 1,

			INPUT_PLAYER = 0,
			INPUT_CPU = 1,
		};

#if 0
		P_GrpAcv	m_grp_Cst_Player1P2P;	//プレイヤ側 固定表示"1P""2P"
		P_GrpAcv	m_grp_Cst_InputPlayerCOM;	//入力者 固定表示"CPU""Player"

		P_GrpAcv	m_grp_CH_Player1P2P;	//キャラ近傍 プレイヤ表示"1P""2P"
		P_GrpAcv	m_grp_CH_InputCOMPLayer;	//キャラ近傍 入力者表示"CPU""Player"
#endif // 0

		static VEC2 POS_PL_CP_1P;
		static VEC2 POS_PL_CP_2P;


#if 0
		//-----------------------------------------------------
		//ヒット数
		P_GrpAcv	m_grpHitNum;		//"0"~"9"
		P_GrpAcv	m_grpStrHit;		//"Hit"

#endif // 0
		//-----------------------------------------------------
		//アクション名
		P_GrpStr	m_strAction;	
		//ステート名
		P_GrpStr	m_strState;	

	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		void ParamInit ( P_Param pParam );
		void Load ();


		//プレイヤ別(1p,2p)のゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );

		//メインイメージ更新
		void UpdateMainImage ( VEC2 posChara );

		//ゲージ類更新
		void UpdateGauge ( BtlParam btlPrm );

#if 0
		//ヒットストップ時間表示の更新
		void UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );

		//のけぞり時間表示の更新
		void UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );
#endif // 0

#if 0
		void SetPlayer ();
		void SetCPU ();

		void UpdateHitNum ( UINT n );
#endif // 0

		//アクション名表示
		void UpdateActionName ( s3d::String actionName );

		//アクション名表示
		void UpdateStateName ( s3d::String stateName );

		//表示切替
		void On ();
		void Off ();

	private:
		P_Grp MakepGrpPlyr ( s3d::String str );

	};

	using P_DispFrontEnd = std::shared_ptr < DispFrontEnd >;


}	//namespace GAME

