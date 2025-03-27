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

		//最初のステート
		m_state = m_state_Ch;
	}


	_CharaSele_Actor::~_CharaSele_Actor ()
	{
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

