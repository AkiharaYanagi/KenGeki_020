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
#if 0
		m_frontEnd = std::make_shared < DispFrontEnd > ();
		AddpTask ( m_frontEnd );
#endif // 0
		m_frontEnd_all = std::make_shared < DispFrontEnd_all > ();
		AddpTask ( m_frontEnd_all );

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
		m_dispInput->LoadPlayer ( playerID );

#if 0
		m_frontEnd->LoadPlayer ( playerID );
#endif // 0
		m_frontEnd_all->LoadPlayer ( playerID );
	}


	//------------------------
	//シーンパラメータ関連初期化
	void DispChara::ParamInit ( P_Param pParam )
	{
		(void)pParam;
#if 0
		m_frontEnd->ParamInit ( pParam );

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


		(void)pAct;
#if 0
		//ダメージ更新
		m_frontEnd->UpdateDamage ( btlPrm );

		//アクション名更新
		m_frontEnd->UpdateActionName ( pAct->GetName ().c_str (), pScp->GetFrame() );
#endif // 0
	}


	void DispChara::UpdateStateName ( s3d::String stateName )
	{
		(void)stateName;
#if 0
		//ステート名更新
		m_frontEnd->UpdateStateName ( stateName );
#endif // 0
	}

	//---------------------------------------------------------------------

	//メインイメージの更新
	void DispChara::UpdateMainImage ( P_Script pScript, const BtlParam & btlprm )
	{
		//メイン
		m_mainImage->SetColor ( btlprm.GetColor () );
		m_mainImage->UpdateMainImage ( pScript, btlprm );

#if 0
		//フロントエンド更新
		m_frontEnd->UpdateMainImage ( btlprm.GetPos() );
#endif // 0
	}

	//入力更新
	void DispChara::UpdateInput ( P_CharaInput p )
	{
		m_dispInput->UpdateInput ( p );
	}


	//ゲージ類更新
	void DispChara::UpdateGauge ( const BtlParam & btlPrm )
	{
		(void)btlPrm;
#if 0
		m_frontEnd->UpdateGauge ( btlPrm );
#endif // 0
		m_frontEnd_all->UpdateGauge ( btlPrm );
	}

	//ヒット数更新
	void DispChara::UpdateChainHitNum ( const BtlParam & btlPrm )
	{
		(void)btlPrm;
#if 0
		m_frontEnd->UpdateHitNum ( btlPrm );
#endif // 0
	}

	//終了時
	void DispChara::EndBattle ()
	{
#if 0
		m_frontEnd->EndBattle ();
#endif // 0
	}


}	//namespace GAME

