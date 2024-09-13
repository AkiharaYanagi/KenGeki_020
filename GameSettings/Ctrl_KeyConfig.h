//=================================================================================================
//
//	キーコンフィグ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Ctrl_KeyConfig
	{
		//固定 キー種類 見出し
		static const Array < String > keynames;

		//設定個数
		static const uint32 NUM_STG;	//設定個数(p1,p2)
		static const uint32 NUM_ROW;	//行
		static const uint32 NUM_CLM;	//列


		//設定したキー種類 表示
		Array < DeviceInput > device_inputs;
		Array < String > di_strs;

		//表示用
		Font font { 20 };

		//選択位置
		size_t selected_index = 0;

		//対象ファイルパス
		s3d::String filePath{ U"filePath" };

		//状態表示
		s3d::String strDiag { U"Init." };

	public:
		Ctrl_KeyConfig ();
		Ctrl_KeyConfig ( const Ctrl_KeyConfig & rhs ) = delete;
		~Ctrl_KeyConfig ();

		void Load();
		void Init ();
		void Move ();
		void Draw ();

		void Save ( s3d::Optional < FilePath > path );
		void Load ( s3d::Optional < FilePath > path );


		s3d::String GamePadInput_ToString ( GamePadInput gpi );
		s3d::String DeviceInput_ToString ( DeviceInput di );

	private:
		static const char32_t * FILE_NAME;
	};


}	//namespace GAME

