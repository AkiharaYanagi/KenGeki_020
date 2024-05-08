//=================================================================================================
//
// LoadCharaBinUtl_s3d ヘッダファイル
//
//=================================================================================================
#pragma once
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using P_Byte = std::unique_ptr < byte [] >;
	using L_UINT = std::unique_ptr < UINT [] >;

	//------------------------------------------------------------
	//	LoadCharaBinで用いる関数群
	//------------------------------------------------------------
	class LoadCharaBinUtl_s3d
	{
	public:
		LoadCharaBinUtl_s3d ();
		LoadCharaBinUtl_s3d ( const LoadCharaBinUtl_s3d & rhs ) = delete;
		~LoadCharaBinUtl_s3d () = default;

		//----
		tstring LoadText ( P_Byte buf, UINT & pos );
		s3d::String LoadString ( P_Byte buf, UINT & pos );
		bool LoadBool ( P_Byte buf, UINT & pos );
		byte LoadByte ( P_Byte buf, UINT & pos );
		int LoadInt ( P_Byte buf, UINT & pos );
		UINT LoadUInt ( P_Byte buf, UINT & pos );
		VEC2 LoadVec2 ( P_Byte buf, UINT & pos );
		VEC2 LoadVec2_Dev10F ( P_Byte buf, UINT & pos );
		RECT LoadRect ( P_Byte buf, UINT & pos );
		void LoadListRect ( P_Byte buf, UINT & pos, PV_RECT pvRect );
		L_UINT LoadAryUint ( P_Byte buf, UINT & pos, UINT & refLength );
		void LoadAryUint ( P_Byte buf, UINT & pos, V_UINT & refAryUint );
	};


}	//namespace GAME


