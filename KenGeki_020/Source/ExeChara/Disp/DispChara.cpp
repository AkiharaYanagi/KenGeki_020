//=================================================================================================
//
// DispChara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispChara.h"
#include "Chara.h"
#include "../BtlParam.h"


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

		//入力表示
		m_dispInput = std::make_shared < DispInput > ();
		AddpTask ( m_dispInput );

		//枠
		m_dispRect = std::make_shared < DispRect > ();
		AddpTask ( m_dispRect );

		//フロントエンド
		m_frontEnd = std::make_shared < DispFrontEnd > ();
		AddpTask ( m_frontEnd );
	}


	DispChara::~DispChara ()
	{
	}

	void DispChara::Move ()
	{
		TASK_VEC::Move ();
	}

	//プレイヤIDを設定
	void DispChara::LoadPlayer ( PLAYER_ID playerID )
	{
		m_frontEnd->LoadPlayer ( playerID );
		m_dispInput->LoadPlayer ( playerID );
	}


	//------------------------
	//シーンパラメータ関連初期化
	void DispChara::ParamInit ( P_Param pParam )
	{
		m_frontEnd->ParamInit ( pParam );

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

	//枠データを設定
	void DispChara::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect->SetCharaRect ( pCharaRect );
	}


	//---------------------------------------------------------------------

	//全体更新
	void DispChara::Update ( P_Action pAct, P_Script pScp, const BtlParam & btlPrm, P_CharaInput pChIpt )
	{
		//メインイメージの更新
		UpdateMainImage ( pScp, btlPrm );

		//枠
		m_dispRect->Update ();

		//入力更新
		UpdateInput ( pChIpt );

		//ゲージ類更新
		UpdateGauge ( btlPrm );

		//ヒット数更新
		UpdateChainHitNum ( btlPrm );

		//ダメージ更新
		m_frontEnd->UpdateDamage ( btlPrm );

		//アクション名更新
		m_frontEnd->UpdateActionName ( pAct->GetName ().c_str () );
	}


	void DispChara::UpdateStateName ( s3d::String stateName )
	{
		//ステート名更新
		m_frontEnd->UpdateStateName ( stateName );
	}

	//---------------------------------------------------------------------

	//メインイメージの更新
	void DispChara::UpdateMainImage ( P_Script pScript, const BtlParam & btlprm )
	{
		//メイン
		m_mainImage->SetColor ( btlprm.GetColor () );
		m_mainImage->UpdateMainImage ( pScript, btlprm );

		//フロントエンド更新
		m_frontEnd->UpdateMainImage ( btlprm.GetPos() );
	}

	//入力更新
	void DispChara::UpdateInput ( P_CharaInput p )
	{
		m_dispInput->UpdateInput ( p );
	}


	//ゲージ類更新
	void DispChara::UpdateGauge ( const BtlParam & btlPrm )
	{
		m_frontEnd->UpdateGauge ( btlPrm );
	}

	//ヒット数更新
	void DispChara::UpdateChainHitNum ( const BtlParam & btlPrm )
	{
		m_frontEnd->UpdateHitNum ( btlPrm );
	}

	//終了時
	void DispChara::EndBattle ()
	{
		m_frontEnd->EndBattle ();
	}


}	//namespace GAME

