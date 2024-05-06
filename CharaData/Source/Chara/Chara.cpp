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
		mpap_tx = std::make_shared < AP_Tx > ();
		m_pvpAction = std::make_shared < VP_Action > ();
//		m_pvpTxEf = std::make_shared < VP_TxBs > ();
		mpap_txEf = std::make_shared < AP_Tx > ();
		m_pvpEf = std::make_shared < VP_Effect > ();
	}

	Chara::~Chara ()
	{
	}

#if 0
	void Chara::Clear ()
	{
		//再読込時はCharaごと行う
		for ( auto p : * m_pvpTxMain ) { p->Rele (); } m_pvpTxMain->clear (); m_pvpTxMain.reset ();
		for ( auto p : * m_pvpAction ) { p->Rele (); } m_pvpAction->clear (); m_pvpAction.reset ();
		for ( auto p : * m_pvpTxEf ) { p->Rele (); } m_pvpTxEf->clear (); m_pvpTxEf.reset ();
		for ( auto p : * m_pvpEf ) { p->Rele (); } m_pvpEf->clear (); m_pvpEf.reset ();
	}
#endif // 0

	//---------------------------------------------------
	//アクション配列にまとめて追加
	void Chara::AddpAction ( std::unique_ptr < P_Action [] > arypAction, rsize_t size )
	{
		if ( ! m_pvpAction ) { return; }

		m_pvpAction->clear ();
		m_pvpAction->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			( *m_pvpAction ) [ i ] = arypAction [ i ];
		}
	}
	void Chara::AddpAction ( std::shared_ptr < P_Action [] > arypAction, rsize_t size )
	{
		if ( ! m_pvpAction ) { return; }

		m_pvpAction->clear ();
		m_pvpAction->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			( *m_pvpAction ) [ i ] = arypAction [ i ];
		}
	}
	void Chara::AddpAction ( const std::vector < P_Action > & arypAction, rsize_t size )
	{
		if ( ! m_pvpAction ) { return; }

		m_pvpAction->clear ();
		m_pvpAction->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			(*m_pvpAction) [ i ] = arypAction [ i ];
		}
	}

	//---------------------------------------------------
	//エフェクト配列にまとめて追加
	void Chara::AddpEffect ( std::unique_ptr < P_Effect [] > arypEffect, rsize_t size )
	{
		if ( ! m_pvpEf ) { return; }

		m_pvpEf->clear ();
		m_pvpEf->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			m_pvpEf->at ( i ) = arypEffect [ i ];
		}
	}
	void Chara::AddpEffect ( const std::vector < P_Effect > & arypEffect, rsize_t size )
	{
		if ( ! m_pvpEf ) { return; }

		m_pvpEf->clear ();
		m_pvpEf->resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			m_pvpEf->at ( i ) = arypEffect [ i ];
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
		for ( auto p : *m_pvpAction )
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

