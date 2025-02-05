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
#include "../../FtgMain/Ef/EfKouAtsu.h"

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

		P_DispAccel	m_gaugeAccel;		//アクセルゲージ
#if	0
		PrmRect		m_gaugeHitStop;			//ヒットストップ時間表示
		PrmRect		m_gaugeLurch;			//のけぞり時間表示
#endif	//0

		P_Grp		m_name_bg;			//名前背景
		P_Grp		m_name;				//名前
		P_Grp		m_face;				//顔
		P_Grp		m_ChouHissatsu;		//超必殺
		CHARA_NAME	m_chara_name { CHARA_OUKA };	//キャラ名保存

		//剣撃抗圧
		P_EfKouAtsu	m_taikou;

		//-----------------------------------------------------

		enum DISP_FE_CONST
		{
			SIDE_1P = 0,
			SIDE_2P = 1,

			INPUT_PLAYER = 0,
			INPUT_CPU = 1,
		};

#if 0
#endif // 0
		P_Grp	m_grp_Cst_Player1P2P;	//プレイヤ側 固定表示"1P""2P"
		P_Grp	m_grp_Cst_InputPlayerCOM;	//入力者 固定表示"CPU""Player"

		P_Grp	m_grp_CH_Player1P2P;	//キャラ近傍 プレイヤ表示"1P""2P"
		P_Grp	m_grp_CH_InputCOMPLayer;	//キャラ近傍 入力者表示"CPU""Player"



		//-----------------------------------------------------
		//ヒット数
		P_Grp		m_grpHitNum;		//"0"~"9"
		P_Grp		m_grpStrHit;		//"Hit"
		P_GrpStr	m_strDmg;			//ダメージ
		P_GrpStr	m_strRevise;		//補正

		//-----------------------------------------------------
		//デバッグ用
		
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
		void UpdateGauge ( const BtlParam & btlPrm );

		//ダメージ更新
		void UpdateDamage ( const BtlParam & btlPrm );

#if 0
		//ヒットストップ時間表示の更新
		void UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );

		//のけぞり時間表示の更新
		void UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );
#endif // 0

		void SetPlayer ();
		void SetCPU ();
#if 0
#endif // 0

		//ヒット数
		void UpdateHitNum ( const BtlParam & btlPrm );

		//アクション名表示
		void UpdateActionName ( s3d::String actionName, UINT frame );

		//アクション名表示
		void UpdateStateName ( s3d::String stateName );

		//表示切替
		void On ();		//すべて
		void Off ();	

		void On_Debug ();
		void Off_Debug ();	//デバッグ用

		void On_DispPlayerInput ();
		void Off_DispPlayerInput ();

		//終了時
		void EndBattle ();

	private:
		P_Grp MakepGrpPlyr ( s3d::String str );

		static const VEC2 POS_PL_CP_1P;
		static const VEC2 POS_PL_CP_2P;
		static const float FACE_X;
		static const float FACE_Y;
		static const float FACE_W;
		static const float CHOU_X;
		static const float CHOU_Y;
		static const float CHOU_W;

		static const float NAME_BG_X;
		static const float NAME_BG_Y;
		static const float NAME_BG_W;

		static const float NAME_X;
		static const float NAME_Y;
		static const float NAME_OUKA_W;
		static const float NAME_SAE_W;
		static const float NAME_RETSUDOU_W;

		static const float NAME_W [ 4 ];

		static const float DMG_X;
		static const float DMG_Y;
	};

	using P_DispFrontEnd = std::shared_ptr < DispFrontEnd >;


}	//namespace GAME

