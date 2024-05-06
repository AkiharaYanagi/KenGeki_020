//=================================================================================================
//	Route ヘッダファイル
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Define.h"
#include "Branch.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	ルート
	//		ブランチの集合
	//================================================================
	
	class Route
	{
		tstring		m_name;				//名前
		std::vector < UINT >		m_vIdBranch;

	public:
		Route ();
		Route ( const Route & rhs ) = delete;
		~Route ();

		//名前
		tstring GetName () const { return m_name; }
		void SetName ( tstring name ) { m_name.assign ( name ); }

		//データ設定
		void SetaIdBranch ( std::unique_ptr < UINT [] > aryId, UINT size )
		{
			m_vIdBranch.clear ();
			m_vIdBranch.resize ( size );
			for ( UINT i = 0; i < size; ++ i )
			{
				m_vIdBranch [ i ] = aryId [ i ];
			}
		}

		void Clear ();

		void AddBranchID ( UINT branchId );

		const V_UINT & GetcvIDBranch () const { return m_vIdBranch; }
		V_UINT & GetvIDBranch () { return m_vIdBranch; }
	};

	using P_Route = std::shared_ptr < Route >;
	using VP_Route = std::vector < P_Route >;
	using PVP_Route = std::shared_ptr < VP_Route >;


}	//namespace GAME


