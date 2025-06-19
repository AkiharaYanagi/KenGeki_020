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

		//ライフゲージ
 		m_life_value = std::make_shared < GameGraphic > ();
//		m_life_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );
		m_life_value->SetZ ( Z_SHADOW - 0.01f );
		m_life_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_life_value );
		AddpTask ( m_life_value );

		//剣撃ゲージ
		m_stamina_value = std::make_shared < GameGraphic > ();
		//m_stamina_value->AddTexture_FromArchive ( U"Battle\\stumina_value.png" );
		m_stamina_value->SetZ ( Z_SHADOW - 0.01f );
		m_stamina_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_stamina_value );
		AddpTask ( m_stamina_value );

		//必殺ゲージ
		m_hissatsu_value = std::make_shared < GameGraphic > ();
		//m_hissatsu_value->AddTexture_FromArchive ( U"Battle\\hissatsu_value.png" );
		m_hissatsu_value->SetZ ( Z_SHADOW - 0.01f );
		m_hissatsu_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_hissatsu_value );
		AddpTask ( m_hissatsu_value );

		//アクセルゲージ
		m_accel_value = std::make_shared < GameGraphic > ();
		m_accel_value->AddTexture_FromArchive ( U"Battle\\accel_value.png" );
		m_accel_value->SetZ ( Z_SHADOW - 0.01f );
//m_life_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
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

			//2pが正方向なので水平反転
			m_gauge_all_bg->SetScaling ( -1.f, 1.f );



			//-----------------------------------------------------------------
			//体力ゲージ
			//Size ( 320, 20 ) //上辺310
			//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
#if 0
			double x0 = 640 - 151 - 10 - 310;	//169
			double x1 = 640 - 151 - 10;			//479
			double x2 = 640 - 151;				//489
			double x3 = 640 - 151 - 310;		//179
#endif // 0
			s3d::Array < s3d::Vec2 > aryVec_life{ {169, 62}, {479, 62}, {489, 82}, {179, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec_life );
			m_life_value->SetpPolygon ( m_life_mask );
			m_life_value->SetPosInMask ( VEC2 (169, 62) );
			m_life_value->AddTexture_FromArchive_mrr ( U"Battle\\life_value.png" );


			//-----------------------------------------------------------------
			//剣撃ゲージ
			//Size ( 309, 16 ) //上辺299
			//const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_1P ( WND_CNT - 141, 86 );
#if 0
			double x0 = 640 - 141 - 10 - 299;	//179
			double x1 = 640 - 141 - 10;			//489
			double x2 = 640 - 141;				//499
			double x3 = 640 - 141 - 299;		//189
#endif // 0
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {179, 86}, {489 , 86}, {499, 102}, {189, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetPosInMask ( VEC2 (189, 86) );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
			m_stamina_value->AddTexture_FromArchive_mrr ( U"Battle\\stumina_value.png" );


			//-----------------------------------------------------------------
			//超必殺技ゲージ
			//Size ( 202, 32 )
			//const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_1P ( WND_CNT - 243, 105 );
#if 0
			double x0 = 640 - 243 - 10 - 192;	//195
			double x1 = 640 - 243 - 10;			//387
			double x2 = 640 - 243;				//397
			double x3 = 640 - 243 - 192;		//205
#endif // 0
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {195, 105}, {387, 105}, {397, 137}, {205, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetPosInMask ( VEC2 (195, 105) );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
			m_hissatsu_value->AddTexture_FromArchive_mrr ( U"Battle\\hissatsu_value.png" );


			//-----------------------------------------------------------------
			//アクセルゲージ
			//Size ( 80, 139 )
			//const VEC2 DispFrontEnd_all::POS_ACCEL_VALUE_1P ( 0 + 75 + 11, 27 );

		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gauge_all_bg->SetPos ( POS_FRAME_ALL_2P );


			//-----------------------------------------------------------------
			//体力ゲージ
			//Size ( 320, 20 ) //上辺310
			//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );
			s3d::Array < s3d::Vec2 > aryVec_life{ {801, 62}, {801 + 310, 62}, {791 + 310, 82}, {791, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec_life );
			m_life_value->SetPosInMask ( VEC2 (791, 62) );
			m_life_value->SetpPolygon ( m_life_mask );
			m_life_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );

			//-----------------------------------------------------------------
			//剣撃ゲージ
			//Size ( 309, 16 )
			//const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {791, 86}, {791 + 299 , 86}, {781 + 299, 102}, {781, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetPosInMask ( VEC2 (781, 86) );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
			m_stamina_value->AddTexture_FromArchive ( U"Battle\\stumina_value.png" );

			//-----------------------------------------------------------------
			//超必殺技ゲージ
			//Size ( 202, 32 )
			//const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {883+10, 105}, {883+202+10, 105}, {883+202-10, 137}, {883-10, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetPosInMask ( VEC2 (883, 105) );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
			m_hissatsu_value->AddTexture_FromArchive ( U"Battle\\hissatsu_value.png" );

			//-----------------------------------------------------------------
			//アクセルゲージ
			//Size ( 80, 139 )
			//const VEC2 DispFrontEnd_all::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );
		}

	}

	//------------------------
	//更新

	//ゲージ
	void DispFrontEnd_all::UpdateGauge ( const BtlParam & btlPrm )
	{
		//体力ゲージ
		int32 life = btlPrm.GetLife () ;
		//（ 最大幅 * 値 / 最大値 ）
		float width_life = 310.f * life /(float)LIFE_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 151 - 10 - width_life;
			double x1 = 640 - 151 - 10;
			double x2 = 640 - 151;
			double x3 = 640 - 151 - width_life;

			s3d::Array < s3d::Vec2 > aryVec_life{ {x0, 62}, {x1, 62}, {x2, 82}, {x3, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec_life );
			m_life_value->SetpPolygon ( m_life_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x1 = 801 + width_life;
			double x2 = 791 + width_life;
			s3d::Array < s3d::Vec2 > aryVec{ {801, 62}, {x1, 62}, {x2, 82}, {791, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec );
			m_life_value->SetpPolygon ( m_life_mask );
		}



		//剣撃ゲージ
		int32 stamina = btlPrm.GetBalance () ;
		//（ 最大幅 * 値 / 最大値 ）
		float width_stamina = 299.f * stamina /(float)BALANCE_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 141 - 10 - width_stamina;
			double x1 = 640 - 141 - 10;
			double x2 = 640 - 141;
			double x3 = 640 - 141 - width_stamina;
			//剣撃ゲージ
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {x0, 86}, {x1, 86}, {x2, 102}, {x3, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x1 = 791 + width_stamina;
			double x2 = 781 + width_stamina;
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {791, 86}, {x1, 86}, {x2, 102}, {781, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
		}


		//超必殺技ゲージ
		int32 hissatsu = btlPrm.GetMana () ;
		//（ 最大幅 * 値 / 最大値 ）
		float width_hissatsu = (202.f - 10) * hissatsu /(float)MANA_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 243 - width_hissatsu - 20;		//195
			double x1 = 640 - 243 - 10;						//387
			double x2 = 640 - 243 + 10;							//397
			double x3 = 640 - 243 - width_hissatsu;		//205
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {x0, 105}, {x1, 105}, {x2, 137}, {x3, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x0 = 640 + 243 + 10;		//893
			double x1 = 640 + 243 + width_hissatsu + 20;
			double x2 = 640 + 243 + width_hissatsu;
			double x3 = 640 + 243 - 10;		//873
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {x0, 105}, {x1, 105}, {x2, 137}, {x3, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
		}


#if 0

		//アクセル

#endif // 0
	}



#pragma region CONST
	//定数
	//2pが正方向, 1p側は(右端が基準点)

	//全体枠
	//Size ( 516, 172 )
	const VEC2 DispFrontEnd_all::POS_FRAME_ALL_1P ( 0 + 516, 10 );
	const VEC2 DispFrontEnd_all::POS_FRAME_ALL_2P ( 1280 - 516 - 0, 10 );

	//体力ゲージ
	//Size ( 320, 20 )
	const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
	const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );

	//剣撃ゲージ
	//Size ( 309, 16 )
	const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_1P ( WND_CNT - 141, 86 );
	const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );

	//超必殺技ゲージ
	//Size ( 202, 32 )
	const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_1P ( WND_CNT - 243, 105 );
	const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );

	//アクセルゲージ
	//Size ( 80, 139 )
	const VEC2 DispFrontEnd_all::POS_ACCEL_VALUE_1P ( 0 + 75 + 11, 27 );
	const VEC2 DispFrontEnd_all::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );

#pragma endregion



}	//namespace GAME

