﻿//=================================================================================================
//
// DispGauge ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispGauge.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

#pragma region CONST

//	constexpr int32 CX_GAUGE_W = 500;		//表示幅
//	constexpr int32 CX_GAUGE_MAX = 10000;	//最大量

//	const float DispGauge::UNIT_LGS = 1.f * CX_GAUGE_W / CX_GAUGE_MAX;//1単位あたりの表示長さ
	const float DispGauge::LIFE_Y_REV = -20;
//	const float DispGauge::LIFE_Y_REV = -0;
//	const float DispGauge::LIFE_H_REV = +50;
	const float DispGauge::LIFE_H_REV = +0;


	const float DispGauge::Z_GAUGE_FRAME	= 0.06f;
	const float DispGauge::Z_GAUGE_DECREASE	= 0.04f;
	const float DispGauge::Z_GAUGE_WHITE	= 0.02f;
	const float DispGauge::Z_GAUGE_VALUE	= 0.01f;

#pragma endregion



	DispGauge::DispGauge ()
	{
#if 0
		//枠
		m_Frame = make_shared < PrmRect > ();
		m_Frame->SetZ ( Z_SYS );
		AddpTask ( m_Frame );
		GRPLST_INSERT_MAIN ( m_Frame );

		//白ダメージ
		m_white = make_shared < PrmRect > ();
		m_white->SetZ ( Z_SYS );
		AddpTask ( m_white );
		GRPLST_INSERT_MAIN ( m_white );

		//減少分
		m_Decrease = make_shared < PrmRect > ();
		m_Decrease->SetZ ( Z_SYS );
		AddpTask ( m_Decrease );
		GRPLST_INSERT_MAIN ( m_Decrease );

		//現在値
		m_Value = make_shared < PrmRect > ();
		m_Value->SetZ ( Z_SYS );
		AddpTask ( m_Value );
		GRPLST_INSERT_MAIN ( m_Value );

		m_white->SetColorN ( 0, 0xffffffff );
		m_white->SetColorN ( 1, 0xffc0c0c0 );
		m_white->SetColorN ( 2, 0xffffffff );
		m_white->SetColorN ( 3, 0xffe0e0e0 );
		m_white->SetValid ( F );

#endif // 0

		//画像

		//枠
		m_grp_Frame = std::make_shared < GameGraphic > ();
		AddpTask ( m_grp_Frame );
		GRPLST_INSERT ( m_grp_Frame );

		//減少分(赤)
		m_grp_Decrease = std::make_shared < GameGraphic > ();
		AddpTask ( m_grp_Decrease );
		GRPLST_INSERT ( m_grp_Decrease );

		//回復分(白)
		m_grp_White = std::make_shared < GameGraphic > ();
		AddpTask ( m_grp_White );
		GRPLST_INSERT ( m_grp_White );

		//値
		m_grp_Value = std::make_shared < GameGraphic > ();
		AddpTask ( m_grp_Value );
		GRPLST_INSERT ( m_grp_Value );
	}

	DispGauge::~DispGauge ()
	{
	}


	void DispGauge::SetPosition ( float x, float y, float w, float h )
	{
		m_base_x = x;
		m_base_y = y;
		m_base_w = w;
		m_base_h = h;
	}

	void DispGauge::SetZ ( float z )
	{
		m_grp_Frame->		SetZ ( z + Z_GAUGE_FRAME );
		m_grp_Decrease->	SetZ ( z + Z_GAUGE_DECREASE );
		m_grp_White->		SetZ ( z + Z_GAUGE_WHITE );
		m_grp_Value->		SetZ ( z + Z_GAUGE_VALUE );

		//Z値の更新のため描画リストの更新
		GRPLST_REMOVE ( m_grp_Frame );
		GRPLST_REMOVE ( m_grp_Decrease );
		GRPLST_REMOVE ( m_grp_White );
		GRPLST_REMOVE ( m_grp_Value );

		GRPLST_INSERT ( m_grp_Frame );
		GRPLST_INSERT ( m_grp_Decrease );
		GRPLST_INSERT ( m_grp_White );
		GRPLST_INSERT ( m_grp_Value );
	}

	void DispGauge::SetTextureName_Frame ( s3d::String textureName )
	{
		m_grp_Frame->AddTexture_FromArchive ( textureName );
	}

	void DispGauge::SetTextureName_Value ( s3d::String textureName )
	{
		m_grp_Value->AddTexture_FromArchive ( textureName );
	}

	void DispGauge::SetTextureName_Decrease ( s3d::String textureName )
	{
		m_grp_Decrease->AddTexture_FromArchive ( textureName );
	}

	void DispGauge::SetTextureName_White ( s3d::String textureName )
	{
		m_grp_White->AddTexture_FromArchive ( textureName );
	}

#if 0

	void DispGauge::SetColor_Frame ( _CLR c )
	{
//		m_Frame->SetAllColor ( c );
	}

	void DispGauge::SetColor_Decrease ( _CLR c )
	{
//		m_Decrease->SetAllColor ( c );
		m_grp_Decrease->SetColor ( c );
	}

	void DispGauge::SetColor_Value ( _CLR c0, _CLR c1, _CLR c2, _CLR c3 )
	{
#if 0
		m_Value->SetColorN ( 0, c0 );
		m_Value->SetColorN ( 1, c1 );
		m_Value->SetColorN ( 2, c2 );
		m_Value->SetColorN ( 3, c3 );
#endif // 0

//		m_grp_Value->SetColor ( 0xffff0000 );
	}

#endif // 0

	void DispGauge::LoadPlayer ( PLAYER_ID id )
	{
		m_playerID = id;
		Init ();
	}

	void DispGauge::Init ()
	{
		//値
		m_value = m_start;
		m_dcr = (float)m_base_max;


		//位置
		//　テクスチャは位置計算の基点が中心方向なので、２ｐ側のテクスチャを正とし１ｐ側は反転させる
		// [1P] ========= 99 ========= [2P]
		//		x	 w	　↑	↑	 w	  x

		const float Y = m_base_y + LIFE_Y_REV;

		if ( PLAYER_ID_1 == m_playerID )
		{
			const float X = m_base_x + m_base_w;

			m_grp_Frame->SetPos ( X + m_padding, Y - m_padding );
			m_grp_Value->SetPos ( X, Y );
			m_grp_Decrease->SetPos ( X, Y );
			m_grp_White->SetPos ( X, Y );

			//反転
			m_grp_Frame->SetScaling ( VEC2 ( -1.f, 1.f ) );
			m_grp_Value->SetScaling ( VEC2 ( -1.f, 1.f ) );
			m_grp_Decrease->SetScaling ( VEC2 ( -1.f, 1.f ) );
			m_grp_White->SetScaling ( VEC2 ( -1.f, 1.f ) );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			float X = GAME_WINDOW_WIDTH - m_base_x - m_base_w;

			m_grp_Frame->SetPos ( X - m_padding, Y - m_padding );
			m_grp_Value->SetPos ( X, Y );
			m_grp_Decrease->SetPos ( X, Y );
			m_grp_White->SetPos ( X, Y );
		}
	}


	//値の更新
	//◆毎フレーム 実行
	void DispGauge::Update ( int32 value )
	{
//		float x = m_base_x;
//		float y = m_base_y;
//		float w = m_base_w;
//		float h = m_base_h;
//		LONG P = (LONG)m_padding;

		const float Y = m_base_y + LIFE_Y_REV;
		const LONG H = (LONG)( m_base_h + LIFE_H_REV );


		//毎フレーム ダメージ表示を減少させる
		if ( m_grp_Decrease->GetValid () )
		{
			UpdateDecrease ();
		}
		 
		m_value = value;
		UNIT_LGS = m_base_w / m_base_max;
		float ln = UNIT_LGS * m_value;	//表示長さ
		float ln_d = UNIT_LGS * m_dcr;	//ダメージ表示長さ


		//0以外は表示、０のときは非表示
#if	0
		//RECTが０のときに全体表示になってしまうので、透明で代用
		m_grp_Value->SetColor ( m_value == 0 ? 0x00ffffff : 0xffffffff );
		if ( value == 0 )
		{
			ln = 1;
		}
#endif	//0

#if 0
		//Validも切り換えでチェックしてOnになるので、他で代用する
		m_grp_Value->SetValid ( value > 0 );
#endif // 0

#if 0
		if ( value < 100 )
		{
			ln = 1;
		}
#endif // 0
		m_grp_Value->SetColor ( value < 100 ? 0x00ffffff : 0xffffffff );


		//表示
		//@info テクスチャレクトを変更するとき、テクスチャサイズは変更しない
		if ( PLAYER_ID_1 == m_playerID )
		{
			//1p側基準位置
			const float X = m_base_x + m_base_w;

			m_grp_Value->SetPos ( X, Y );

			//表示枠で減少分を設定
			m_grp_Value->SetRectF ( s3d::RectF { 0, 0, (LONG)ln, H } );
//			m_grp_Value->SetRectF ( s3d::RectF { P, 0, (LONG)(ln + P), H } );
//			m_grp_Value->SetRectF ( s3d::RectF { P, 0, (LONG)(ln), H } );

			m_grp_Decrease->SetPos ( X, Y );
			m_grp_Decrease->SetRectF ( s3d::RectF { 0, 0, (LONG)ln_d, H } );
//			m_grp_Decrease->SetRectF ( s3d::RectF { P, 0, (LONG)(ln_d + P), H } );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			//2p側基準位置
			float X = GAME_WINDOW_WIDTH - m_base_x - m_base_w;

			m_grp_Value->SetPos ( X, Y );
			m_grp_Value->SetRectF ( s3d::RectF { 0, 0, (LONG)ln, H } );
//			m_grp_Value->SetRectF ( s3d::RectF { P, 0, (LONG)(ln + P), H } );
//			m_grp_Value->SetRectF ( s3d::RectF { P, 0, (LONG)(ln), H } );

			m_grp_Decrease->SetPos ( X, Y );
			m_grp_Decrease->SetRectF ( s3d::RectF { 0, 0, (LONG)ln_d, H } );
//			m_grp_Decrease->SetRectF ( s3d::RectF { P, 0, (LONG)(ln_d + P), H } );
		}

	}

	void DispGauge::UpdateWhite ( int white )
	{
		float ln = UNIT_LGS * m_value;	//表示長さ
		float wht = UNIT_LGS * white;	//表示長さ

//		float x = m_base_x;
//		float y = m_base_y + LIFE_Y_REV;
//		float w = m_base_w;
//		float h = m_base_h + LIFE_H_REV;
//		LONG P = (LONG)m_padding;

		const float Y = m_base_y + LIFE_Y_REV;
//		const float W = 512;
		const LONG H = (LONG)( m_base_h + LIFE_H_REV );

		//メイン値のサイズを取得
//		float vx = m_grp_Value->GetPos().x;
//		LONG vl = (LONG)m_grp_Value->GetpObject(0)->GetRectF ().w;
//		LONG vr = (LONG)m_grp_Value->GetpObject(0)->GetRectF ().x;
//		float vw = (float)( vr - vl );

		//０のときは非表示
		m_grp_White->SetValid ( white != 0 );


		if ( PLAYER_ID_1 == m_playerID )
		{
			//1p側基準位置
			const float X = m_base_x + m_base_w;

//			m_grp_White->SetPos ( x + P + w, y );
//			m_grp_White->SetRectF ( s3d::RectF { P, 0, (LONG)(ln + P + wht), (LONG)h } );
			m_grp_White->SetPos ( X, Y );
			m_grp_White->SetRectF ( s3d::RectF { 0, 0, (LONG)(ln + wht), H } );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			//2p側基準位置
//			float p2_bx = P + GAME_WINDOW_WIDTH - x - W;	//W = テクスチャサイズ
			float X = GAME_WINDOW_WIDTH - m_base_x - m_base_w;

//			m_grp_White->SetPos ( p2_bx, y );
//			m_grp_White->SetRectF ( s3d::RectF { P, 0, (LONG)(ln + P + wht), (LONG)h } );
			m_grp_White->SetPos ( X, Y );
			m_grp_White->SetRectF ( s3d::RectF { 0, 0, (LONG)(ln + wht), H } );
		}
	}


	//最大値変更
	void DispGauge::ChangeMax ( float percent )
	{
		//初期位置
//		float x = m_base_x;
//		float y = m_base_y;
		float w = m_base_w * percent * 0.01f;
		float h = m_base_h;
		const LONG H = (LONG)( h + LIFE_H_REV );
		const LONG W = (LONG)w;

		if ( PLAYER_ID_1 == m_playerID )
		{
			m_grp_Frame->SetRectF ( s3d::RectF { 0, 0, W, H } );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_grp_Frame->SetRectF ( s3d::RectF { 0, 0, W, H } );
		}
	}


	void DispGauge::On ()
	{
		m_grp_Value->SetValid ( T ); 
		m_grp_Frame->SetValid ( T ); 
		m_grp_Decrease->SetValid ( T ); 
		m_grp_White->SetValid ( T ); 
	}

	void DispGauge::Off ()
	{
		m_grp_Value->SetValid ( F ); 
		m_grp_Frame->SetValid ( F ); 
		m_grp_Decrease->SetValid ( F ); 
		m_grp_White->SetValid ( F ); 
	}

#if 0
	void DispGauge::GrpOff ()
	{
		m_grp_Frame->SetValid ( F ); 
		m_grp_Value->SetValid ( F ); 
		m_grp_Decrease->SetValid ( F ); 
		m_grp_White->SetValid ( F ); 
	}

	void DispGauge::GrpOn ()
	{
		m_grp_Frame->SetValid ( T ); 
		m_grp_Value->SetValid ( T ); 
		m_grp_Decrease->SetValid ( T ); 
		m_grp_White->SetValid ( T ); 
	}
#endif // 0

	void DispGauge::UpdateDecrease ()
	{
		//@info
		//加速度をつけることで少ないダメージは長く、大きいダメージは相対的に短くする

		//メイン値と減少値が異なるとき開始
		bool bDisp = m_value < m_dcr;
		if ( m_wait == 0 && bDisp )
		{
			m_wait = 1;
		}

		if ( 0 < m_wait )
		{
			//ウェイト終了
			if ( m_wait ++ > 30 )
			{
				m_wait = 0;
				bStart = T;
			}
		}

		if ( bStart )
		{
			if ( m_value < m_dcr )
			{
				m_vel += m_acc;
				m_dcr -= (int)m_vel;
			}

			//追いついたら終了
			if ( m_dcr < m_value )
			{
				m_dcr = 1.f * m_value;
				m_vel = 1.f;
				bStart = F;
			}
		}

		if ( PLAYER_ID_1 == m_playerID )
		{
//			DBGOUT_WND_F ( 6, _T ( "bDisp = %d, wait = %02d, bStart = %d" ), bDisp ? 1: 0, m_wait, bStart ? 1: 0 );
		}

		//０のときは非表示
		m_grp_Decrease->SetValid ( m_dcr <= 0 );
	}


}	//namespace GAME

