//=================================================================================================
//
//	EfHit ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfHit.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//拡大tan(ω)用
	const float EfHit::OMEGA = D3DX_PI_HALF / ( 30 );

	EfHit::EfHit ()
		: m_tx_rev ( VEC2 ( 0, 0 ) ), m_center ( VEC2 ( 0, 0 ) ), m_dispBase ( VEC2 ( 0, 0 ) )
	{
		AddTexture ( U"Ef_Hit.png" );

		m_count = 0;
#if 0
		SetStartScaling ( VEC2 ( 1.f, 1.f ) );
		SetTargetScaling ( VEC2 ( 2.f, 2.f ) );
		SetVel ( VEC2 ( 0.1f, 1.f ) );
#endif // 0

		SetValid ( F );
	}

	EfHit::~EfHit ()
	{
	}

	void EfHit::TxLoad ()
	{
//		GameGraphic::TxLoad ();

		//テクスチャの読込後
		VEC2 center = GetCenterOfTexture ( 0 );
		SetScalingCenter ( center );	//拡縮の中心
		SetRotationCenter ( center );	//回転の中心
		m_tx_rev -= center;
		SetPos ( m_tx_rev );
	}

	void EfHit::On ( VEC2 center )
	{
		//稼働開始
		SetValid ( T );

		//位置
		m_center = center;

		//フェード([F],カラー)
		SetFadeOut ( 30, 0x80ffffff );

		//回転角(ランダム)
		float rad = D3DX_2PI / 360;
		int random = rand () % 360;
		SetRadian ( rad * random );

		//拡縮
		m_count = 0;
	}

	void EfHit::Move ()
	{
		//非アクティブ時は何もしない
		if ( ! GetValid () ) { GrpAcv::Move (); return; }

		float scale = 1.f;
		if ( OMEGA * m_count >= D3DX_PI_HALF )
		{
			scale = 100.f;
		}
		else
		{
			scale = tanf ( OMEGA * m_count );
		}

		SetScaling ( scale, scale );

		++ m_count;
//		m_count += 2;
		if ( OMEGA * m_count >= D3DX_PI_HALF ) { m_count = 0; }


		//画面位置補正
		m_dispBase = G_BASE_POS ();

		//中心位置 + 外部補正位置
		SetPos ( m_tx_rev + m_center + m_dispBase );

		GrpAcv::Move ();
	}
}
