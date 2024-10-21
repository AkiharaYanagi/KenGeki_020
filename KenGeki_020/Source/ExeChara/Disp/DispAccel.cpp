//=================================================================================================
//
// DispAccel ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispAccel.h"
#include "DispChara_Const.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float DispAccel::BG_POS_X_1P = 30.f;
	const float DispAccel::BG_POS_X_2P = 1280 - BG_POS_X_1P;
	const float DispAccel::BG_POS_Y = 835.f;

	const float DispAccel::HND_POS_X_1P = 72.f + 8.f;
	const float DispAccel::HND_POS_X_2P = 1280 - HND_POS_X_1P;
	const float DispAccel::HND_POS_Y = BG_POS_Y - 3;

	const float DispAccel::HND_ROT_X = 8.f;
	const float DispAccel::HND_ROT_Y = 64.f;

	const float DispAccel::Z_GAUGE_ACCEL = Z_SHADOW + 0.08f;



	DispAccel::DispAccel ()
	{
		//アクセルゲージ
		m_gaugeAccel = std::make_shared < GameGraphic > ();
		m_gaugeAccel->AddTexture_FromArchive ( U"gauge_accel_frame.png" );
		m_gaugeAccel->SetZ ( Z_GAUGE_ACCEL );
		m_gaugeAccel->SetScalingCenter ( VEC2 ( 0, 128.f ) );
		AddpTask ( m_gaugeAccel );
		GRPLST_INSERT ( m_gaugeAccel );

		//アクセルゲージ針
		m_gaugeAccelHand = std::make_shared < GameGraphic > ();
		m_gaugeAccelHand->AddTexture_FromArchive ( U"gauge_accel_hand.png" );
		m_gaugeAccelHand->SetZ ( Z_GAUGE_ACCEL );
		AddpTask ( m_gaugeAccelHand );
		GRPLST_INSERT ( m_gaugeAccelHand );

	}

	DispAccel::~DispAccel ()
	{
	}

	void DispAccel::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;

		//プレイヤー別初期化位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_gaugeAccel->SetPos ( BG_POS_X_1P, BG_POS_Y );

			m_gaugeAccelHand->SetPos ( HND_POS_X_1P, HND_POS_Y );
			m_gaugeAccelHand->SetRotationCenter ( VEC2 ( + HND_ROT_X, HND_ROT_Y ) );
			m_gaugeAccelHand->SetRadian ( - D3DX_PI_HALF );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gaugeAccel->SetScaling ( -1.f, 1.f );
			m_gaugeAccel->SetPos ( BG_POS_X_2P, BG_POS_Y );

			m_gaugeAccelHand->SetScaling ( -1.f, 1.f );
			m_gaugeAccelHand->SetPos ( HND_POS_X_2P, HND_POS_Y );
			m_gaugeAccelHand->SetRotationCenter ( VEC2 ( - HND_ROT_X, HND_ROT_Y ) );
			m_gaugeAccelHand->SetRadian ( + D3DX_PI_HALF );
		}
	}

	void DispAccel::Update ( int value )
	{
		//角度方向
		float dir = 1.f;
		if ( PLAYER_ID_1 == m_playerID )
		{
			dir = -1.f;
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			dir = 1.f;
		}

#if 0
		static int test_value = 0;
		static int test_vel = 20;

		test_value += test_vel;

		// -500 ~ +1000
		if ( test_value < -500 ) { test_vel = 20; }
		if ( 1000 < test_value ) { test_vel = -20; }

		//角度変換
		float rad = ( 1000 - test_value ) * (dir / 2000) * D3DX_PI;

		m_gaugeAccelHand->SetRadian ( rad );
//		m_gaugeAccelHand->SetRadian ( D3DX_PI * 0.5f );
#endif // 0

		//角度変換
		float rad = ( 1000 - value ) * (dir / 2000) * D3DX_PI;

		m_gaugeAccelHand->SetRadian ( rad );
	}

	void DispAccel::On ()
	{
		m_gaugeAccel->SetValid ( T );
		m_gaugeAccelHand->SetValid ( T );
	}

	void DispAccel::Off ()
	{
		m_gaugeAccel->SetValid ( F );
		m_gaugeAccelHand->SetValid ( F );
	}



}	//namespace GAME

