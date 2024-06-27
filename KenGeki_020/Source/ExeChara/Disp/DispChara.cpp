//=================================================================================================
//
// DispChara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispChara::DispChara ()
	{
		//キャラメイングラフィック
		m_mainImage = std::make_shared < DispMainImage > ();
		AddpTask ( m_mainImage );

#if 0
		m_dispRect = make_shared < DispRect > ();
		AddpTask ( m_dispRect );

		m_frontEnd = make_shared < DispFrontEnd > ();
		AddpTask ( m_frontEnd );

		m_dispInput = make_shared < DispInput > ();
		AddpTask ( m_dispInput );

		//影
		m_grpShadow = make_shared < GrpAcv > ();
		m_grpShadow->AddTexture ( _T ( "shadow.png" ) );
		m_grpShadow->SetZ ( Z_SHADOW );
		AddpTask ( m_grpShadow );
		GRPLST_INSERT_MAIN ( m_grpShadow );
#endif // 0
	}


	DispChara::~DispChara ()
	{
	}

#if 0
	//プレイヤIDを設定
	void DispChara::LoadPlayer ( PLAYER_ID playerID )
	{
		m_frontEnd->LoadPlayer ( playerID );
		m_dispInput->LoadPlayer ( playerID );
	}

#endif // 0


	//------------------------
	//シーンパラメータ関連初期化
	void DispChara::ParamInit ( P_Param pParam )
	{
#if 0
		m_frontEnd->ParamInit ( pParam );
		
		OnRect ();
#endif // 0

#if 0

#if DEBUG_DISP
		OnRect ();
#else
		OffRect ();
#endif // DEBUG_DISP

#endif // 0

	}

	//キャラデータを設定
	void DispChara::SetpChara ( const P_Chara pChara )
	{
		m_mainImage->SetpChara ( pChara );
	}

#if 0
	//枠データを設定
	void DispChara::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect->SetCharaRect ( pCharaRect );
	}
#endif // 0



	//全体更新
	void DispChara::Update ( P_Action pAct, P_Script pScp, const BtlParam & btlprm, P_CharaInput pChIpt )
	{
		//メインイメージの更新
		UpdateMainImage ( pScp, btlprm );
#if 0
		//ゲージ類更新
		UpdateGauge ( btlprm );

		//入力更新
		UpdateInput ( pChIpt );

		//ヒット数更新
		UpdateChainHitNum ( btlprm.GetChainHitNum () );

		//アクション名更新
		m_frontEnd->UpdateActionName ( pAct->GetName ().c_str () );
//		m_frontEnd->UpdateActionName ( Format::GetFormatStr ( _T("Frame = %d"), pScp->GetFrame () ).get() );
#endif // 0
	}


	void DispChara::UpdateMainImage ( P_Script pScript, const BtlParam & btlprm )
	{
		//メイン
		m_mainImage->SetColor ( btlprm.GetColor () );
		m_mainImage->UpdateMainImage ( pScript, btlprm );

#if 0
		//影
		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//向き
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//基準位置
		VEC2 vecImgShadow = VEC2 ( bx, 0 ) + posChara + VEC2 ( -128 + fDir * 12, 0 );
		vecImgShadow.y = -0.f + 1.f * PLAYER_BASE_Y;	//y方向のみ指定
		m_grpShadow->SetPos ( vecImgShadow );

		//枠
		m_dispRect->Update ();

		//フロントエンド更新
		m_frontEnd->UpdateMainImage ( posChara );
#endif // 0
	}

#if 0
	//ゲージ類更新
	void DispChara::UpdateGauge ( BtlParam btlPrm )
	{
		m_frontEnd->UpdateGauge ( btlPrm );
	}

	//ヒット数更新
	void DispChara::UpdateChainHitNum ( UINT n )
	{
		m_frontEnd->UpdateHitNum ( n );
	}


#endif // 0

}	//namespace GAME

