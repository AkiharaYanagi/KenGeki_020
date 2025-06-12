//=================================================================================================
//
// DispFrontEnd_all ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispFrontEnd_all.h"
#include "DispChara_Const.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	DispFrontEnd_all::DispFrontEnd_all ()
	{
		//総合ゲージ背景
		m_gauge_all_bg = std::make_shared < GameGraphic > ();
		m_gauge_all_bg->AddTexture_FromArchive ( U"Battle\\gauge_all.png" );
		m_gauge_all_bg->SetZ ( Z_SHADOW );
		GRPLST_INSERT ( m_gauge_all_bg );
		AddpTask ( m_gauge_all_bg );

		//ライフ
 		m_life_value = std::make_shared < GameGraphic > ();
		m_life_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );
		m_life_value->SetZ ( Z_SHADOW - 0.01f );
		GRPLST_INSERT ( m_life_value );
		AddpTask ( m_life_value );

		//スタミナ
		m_stamina_value = std::make_shared < GameGraphic > ();
		m_stamina_value->AddTexture_FromArchive ( U"Battle\\stumina_value.png" );
		m_stamina_value->SetZ ( Z_SHADOW - 0.01f );
		GRPLST_INSERT ( m_stamina_value );
		AddpTask ( m_stamina_value );

		//必殺
		m_hissatsu_value = std::make_shared < GameGraphic > ();
		m_hissatsu_value->AddTexture_FromArchive ( U"Battle\\hissatsu_value.png" );
		m_hissatsu_value->SetZ ( Z_SHADOW - 0.01f );
		GRPLST_INSERT ( m_hissatsu_value );
		AddpTask ( m_hissatsu_value );

		//アクセル
		m_accel_value = std::make_shared < GameGraphic > ();
		m_accel_value->AddTexture_FromArchive ( U"Battle\\accel_value.png" );
		m_accel_value->SetZ ( Z_SHADOW - 0.01f );
		GRPLST_INSERT ( m_accel_value );
		AddpTask ( m_accel_value );
	}

	DispFrontEnd_all::~DispFrontEnd_all ()
	{
	}


	void DispFrontEnd_all::Load ()
	{
		TASK_VEC::Load ();
	}

	//パラメータ初期化
	void DispFrontEnd_all::ParamInit ( P_Param pParam )
	{
		(void)pParam;
	}

	//プレイヤ側で初期化
	void DispFrontEnd_all::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;


		//プレイヤー別初期化位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_gauge_all_bg->SetPos ( POS_FRAME_ALL_1P );
			m_life_value->SetPos ( POS_LIFE_VALUE_1P );
			m_stamina_value->SetPos ( POS_STAMINA_VALUE_1P );
			m_hissatsu_value->SetPos ( POS_HISSATSU_VALUE_1P );
			m_accel_value->SetPos ( POS_ACCEL_VALUE_1P );

			//2pが正方向なので水平反転
			m_gauge_all_bg->SetScaling ( -1.f, 1.f );
			m_life_value->SetScaling ( -1.f, 1.f );
			m_stamina_value->SetScaling ( -1.f, 1.f );
			m_hissatsu_value->SetScaling ( -1.f, 1.f );
			m_accel_value->SetScaling ( -1.f, 1.f );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gauge_all_bg->SetPos ( POS_FRAME_ALL_2P );
			m_life_value->SetPos ( POS_LIFE_VALUE_2P );
			m_stamina_value->SetPos ( POS_STAMINA_VALUE_2P );
			m_hissatsu_value->SetPos ( POS_HISSATSU_VALUE_2P );
			m_accel_value->SetPos ( POS_ACCEL_VALUE_2P );
		}

	}



#pragma region CONST
	//定数
	//2pが正方向, 1p側は(右端が基準点)

	//全体枠
	//Size ( 516, 172 )
	const VEC2 DispFrontEnd_all::POS_FRAME_ALL_1P ( 0 + 516, 10 );
	const VEC2 DispFrontEnd_all::POS_FRAME_ALL_2P ( 1280 - 516 - 0, 10 );

	//ライフ
	//Size ( 320, 20 )
	const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
	const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );

	//スタミナ
	//Size ( 309, 16 )
	const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_1P ( WND_CNT - 141, 86 );
	const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );

	//必殺
	//Size ( 202, 32 )
	const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_1P ( WND_CNT - 243, 105 );
	const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );

	//アクセル
	//Size ( 80, 139 )
	const VEC2 DispFrontEnd_all::POS_ACCEL_VALUE_1P ( 0 + 75 + 11, 27 );
	const VEC2 DispFrontEnd_all::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );

#pragma endregion



}	//namespace GAME

