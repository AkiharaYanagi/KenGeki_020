//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_CharaSele_Actor.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	_CharaSele_Actor::_CharaSele_Actor ()
	{
		//各種ステート
		m_state_Ch  = std::make_shared < ChSl_St_Chara > ();
		m_state_Clr = std::make_shared < ChSl_St_Color > ();
		m_state_Stg = std::make_shared < ChSl_St_Stage > ();
		m_state_BGM = std::make_shared < ChSl_St_BGM > ();
		m_state_OK  = std::make_shared < ChSl_St_OK > ();

		//すべてのステートに登録
		m_aryState.push_back ( m_state_Ch );
		m_aryState.push_back ( m_state_Clr );
		m_aryState.push_back ( m_state_Stg );
		m_aryState.push_back ( m_state_BGM );
		m_aryState.push_back ( m_state_OK );

		//最初のステート
		m_state = m_state_Ch;
	}


	_CharaSele_Actor::~_CharaSele_Actor ()
	{
	}


	void _CharaSele_Actor::PlayerInit ( PLAYER_ID id )
	{
		for ( P_ChSl_St pSt : m_aryState )
		{
			pSt->SetPlayerID ( id );
		}
	}


	void _CharaSele_Actor::Load ()
	{
		//ステートに親アクタポインタを設置
		for ( P_ChSl_St pSt : m_aryState )
		{
			pSt->SetwpActor ( shared_from_this () );
		}
	}

	void _CharaSele_Actor::Move ()
	{
		m_state->Move ();
	}

	void _CharaSele_Actor::Input ()
	{
		m_state->Input ();
	}

	void _CharaSele_Actor::SetwpCharaSele ( WP_CharaSele wp )
	{
		for ( P_ChSl_St pSt : m_aryState )
		{
			pSt->SetwpCharaSele ( wp );
		}
	}

	void _CharaSele_Actor::SetwpChSl_Player ( WP_ChSl_Player wp )
	{
		for ( P_ChSl_St pSt : m_aryState )
		{
			pSt->SetwpPlayer ( wp );
		}
	}

	void _CharaSele_Actor::SetpCursor ( P_ChSl_Cursor p )
	{
		for ( P_ChSl_St pSt : m_aryState )
		{
			pSt->SetpCursor ( p );
		}
	}


	//=====================================================
	//ステート変更
	
	//キャラクタ選択
	void _CharaSele_Actor::Start_Ch ()
	{
		m_state = m_state_Ch;
	}

	//カラー選択
	void _CharaSele_Actor::Start_Clr ()
	{
		m_state = m_state_Clr;
	}

	//ステージ選択
	void _CharaSele_Actor::Start_Stg ()
	{
		m_state = m_state_Stg;
	}

	//BGM選択
	void _CharaSele_Actor::Start_BGM ()
	{
		m_state = m_state_BGM;
	}

	//選択完了
	void _CharaSele_Actor::Start_OK ()
	{
		m_state = m_state_OK;
	}



}	//namespace GAME

