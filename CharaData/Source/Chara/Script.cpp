//=================================================================================================
//	Script ソースファイル
//=================================================================================================
#include "Script.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Script::Script ()
	{
		Make ();
	}

	Script::~Script ()
	{
		m_pvpEfGnrt->clear ();
	}

	void Script::Make ()
	{
		m_pvCRect = std::make_shared < V_RECT > ();
		m_pvARect = std::make_shared < V_RECT > ();
		m_pvHRect = std::make_shared < V_RECT > ();
		m_pvORect = std::make_shared < V_RECT > ();

		m_pvpEfGnrt = std::make_shared < VP_EfGnrt > ();
	}

	void Script::Rele ()
	{
		m_pvpEfGnrt->clear (); m_pvpEfGnrt.reset ();
	}

	void Script::SetRouteID ( std::unique_ptr < UINT[] > up_aryUint, UINT size )
	{
		m_vRouteID.clear ();
		m_vRouteID.resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			m_vRouteID [ i ] = up_aryUint [ i ];
		}
	}


}	//namespace GAME

