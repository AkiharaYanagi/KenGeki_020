//=================================================================================================
//
// DispMainImage ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispMainImage.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispMainImage::DispMainImage ()
	{
		//キャラメイングラフィック
		m_mainGraphic = std::make_shared < GameGraphic > ();
		m_mainGraphic->SetZ ( Z_CH );
		AddpTask ( m_mainGraphic );
		GRPLST_INSERT ( m_mainGraphic );

		//影
		m_grpShadow = std::make_shared < GameGraphic > ();
		m_grpShadow->AddTexture_FromArchive ( U"shadow.png" );
		m_grpShadow->SetZ ( Z_SHADOW );
		AddpTask ( m_grpShadow );
		GRPLST_INSERT ( m_grpShadow );
	}

	DispMainImage::~DispMainImage ()
	{
	}


	void DispMainImage::SetpChara ( P_Chara pChara )
	{
		//キャラのメインテクスチャアレイを設置
		mpap_Tx = pChara->GetpapTxMain ();

		m_mainGraphic->ClearTexture ();
		for ( P_Tx ptx : *mpap_Tx )
		{
			m_mainGraphic->AddpTexture ( ptx );
		}
	}

	//メインイメージの更新
	void DispMainImage::UpdateMainImage ( P_Script pScript, const BtlParam & btlprm )
	{
		VEC2 ptChara = btlprm.GetPos();
		bool dirRight = btlprm.GetDirRight ();

		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//向き
//		float fDir = ( 1.f );		//向き

		//位置
		VEC2 posScript = pScript->GetPos ();
		float bx = G_BASE_POS ().x;	//基準位置
		float x = bx + ptChara.x + fDir * posScript.x;	//反転位置補正
//		float x = bx + ptChara.x + posScript.x;	//->ScalingCenterの指定により位置補正は無し
		float y =  0 + ptChara.y + posScript.y;
		VEC2 vecImg = VEC2 ( x, y );

		//IDチェックはスクリプト作成時、ロード時に行う
		UINT index = pScript->GetImageIndex ();
//		P_Tx pTexture = mpap_Tx->at ( index );


#if 0
		float rad = D3DX_PI * 0.01f * pScript->m_prmStaging.Rotate;		//回転
		m_mainGraphic->SetRadian ( rad * fDir );

		//スクリプトからの指定がなければテクスチャの中心
		VEC2 center { 0, 0 };
		if ( center != pScript->m_prmStaging.Rotate_center )
		{
			center = pScript->m_prmStaging.Rotate_center;
		}
		else
		{
			center = pTexture->GetCenter ();
		}

		m_mainGraphic->SetRotationCenter ( center );
#endif // 0

		//表示に反映
		m_mainGraphic->SetPos ( vecImg );
//		m_mainGraphic->SetScalingCenter ( center );
		m_mainGraphic->SetScaling ( 1.f * fDir, 1.f );

//		m_mainGraphic->SetpTexture ( pTexture );
		m_mainGraphic->SetIndexTexture ( index );

		//---------------------------------------------------------
		//影
		VEC2 vecImgShadow = VEC2 ( bx, 0 ) + ptChara + VEC2 ( -128 + fDir * 12, 0 );
		vecImgShadow.y = -0.f + (float)PLAYER_BASE_Y;	//y方向のみ指定
		m_grpShadow->SetPos ( vecImgShadow );

	}


	void DispMainImage::TurnShadow ( bool b )
	{
		m_mainGraphic->SetColor ( b ? 0xff000000 : 0xffffffff );
	}



}	//namespace GAME

