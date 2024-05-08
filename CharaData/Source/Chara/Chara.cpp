//=================================================================================================
//
//	Chara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Chara::Chara ()
	{
//		m_pvpTxMain = std::make_shared < VP_TxBs > ();
		mpap_txMain = std::make_shared < AP_Tx > ();
		mpap_Action = std::make_shared < AP_Action > ();
//		m_pvpTxEf = std::make_shared < VP_TxBs > ();
		mpap_txEf = std::make_shared < AP_Tx > ();
		mpap_Ef = std::make_shared < AP_Effect > ();
	}

	Chara::~Chara ()
	{
	}

	void Chara::Clear ()
	{
#if 0
		//再読込時はCharaごと行う
		for ( auto p : * m_pvpTxMain ) { p->Rele (); } m_pvpTxMain->clear (); m_pvpTxMain.reset ();
		for ( auto p : * m_pvpAction ) { p->Rele (); } m_pvpAction->clear (); m_pvpAction.reset ();
		for ( auto p : * m_pvpTxEf ) { p->Rele (); } m_pvpTxEf->clear (); m_pvpTxEf.reset ();
		for ( auto p : * m_pvpEf ) { p->Rele (); } m_pvpEf->clear (); m_pvpEf.reset ();
#endif // 0
	}

	//---------------------------------------------------
	//アクション配列にまとめて追加
	void Chara::AddpAction ( std::unique_ptr < P_Action [] > arypAction, rsize_t size )
	{
		if ( ! mpap_Action ) { return; }

		mpap_Action->clear ();
		mpap_Action->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			( *mpap_Action ) [ i ] = arypAction [ i ];
		}
	}
	void Chara::AddpAction ( std::shared_ptr < P_Action [] > arypAction, rsize_t size )
	{
		if ( ! mpap_Action ) { return; }

		mpap_Action->clear ();
		mpap_Action->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			( *mpap_Action ) [ i ] = arypAction [ i ];
		}
	}
	void Chara::AddpAction ( const std::vector < P_Action > & arypAction, rsize_t size )
	{
		if ( ! mpap_Action ) { return; }

		mpap_Action->clear ();
		mpap_Action->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			(*mpap_Action) [ i ] = arypAction [ i ];
		}
	}

	//---------------------------------------------------
	//エフェクト配列にまとめて追加
	void Chara::AddpEffect ( std::unique_ptr < P_Effect [] > arypEffect, rsize_t size )
	{
		if ( ! mpap_Ef ) { return; }

		mpap_Ef->clear ();
		mpap_Ef->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			mpap_Ef->at ( i ) = arypEffect [ i ];
		}
	}
	void Chara::AddpEffect ( const std::vector < P_Effect > & arypEffect, rsize_t size )
	{
		if ( ! mpap_Ef ) { return; }

		mpap_Ef->clear ();
		mpap_Ef->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			mpap_Ef->at ( i ) = arypEffect [ i ];
		}
	}

	//---------------------------------------------------
	void Chara::AddaCommand ( std::unique_ptr < P_Command [] > aryCmd, UINT size )
	{
		m_vpCommand.clear ();
		m_vpCommand.resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			m_vpCommand [ i ] = aryCmd [ i ];
		}
	}

	void Chara::AddaBranch ( std::unique_ptr < P_Branch [] > aryBrc, UINT size )
	{
		m_vpBranch.clear ();
		m_vpBranch.resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			m_vpBranch [ i ] = aryBrc [ i ];
		}
	}

	void Chara::AddaRoute ( std::unique_ptr < P_Route [] > aryRut, UINT size )
	{
		m_vpRoute.clear ();
		m_vpRoute.resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			m_vpRoute [ i ] = aryRut [ i ];
		}
	}


	//---------------------------------------------------
	UINT Chara::GetActionID ( tstring name ) const
	{
		UINT index = 0;
		for ( auto p : *mpap_Action )
		{
			tstring actionName = p->GetName (); 
			if ( 0 == name.compare ( actionName ) )
			{
				return index;
			}
			++index;
		}
		return NO_ACTION;
	}


}	//namespace GAME

