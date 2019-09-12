#pragma once
#include <fstream>
#include <vector>

typedef unsigned int uint;


#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>


enum class StreamMode : uint
{
	Write, Read
};



class FileStream final
{
public:
	FileStream() = default;
	~FileStream() = default;

	bool Open(const std::string& path, const StreamMode& mode);
	void Close();

	//=========================================================
	//Write
	template <typename T, typename = typename std::enable_if<
		std::is_same<T, bool>::value ||
		std::is_same<T, char>::value ||
		std::is_same<T, std::byte>::value ||
		std::is_same<T, int>::value ||
		std::is_same<T, uint>::value ||
		std::is_same<T, long>::value ||
		std::is_same<T, unsigned long>::value ||
		std::is_same<T, long long>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value ||
		std::is_same<T, D3DXVECTOR2>::value ||
		std::is_same<T, D3DXVECTOR3>::value ||
		std::is_same<T, D3DXVECTOR4>::value ||
		std::is_same<T, D3DXQUATERNION>::value ||
		std::is_same<T, D3DXCOLOR>::value ||
		std::is_same<T, D3DXMATRIX>::value
	>::type> void Write(const T& value)
	{
		out.write(reinterpret_cast<const char*>(&value), sizeof(T));
	}

	void Write(const std::string& value);
	void Write(const std::vector<std::byte>& value);
	//=========================================================

	//=========================================================
	//Read
	template <typename T, typename = typename std::enable_if<
		std::is_same<T, bool>::value ||
		std::is_same<T, char>::value ||
		std::is_same<T, std::byte>::value ||
		std::is_same<T, int>::value ||
		std::is_same<T, uint>::value ||
		std::is_same<T, long>::value ||
		std::is_same<T, unsigned long>::value ||
		std::is_same<T, long long>::value ||
		std::is_same<T, float>::value ||
		std::is_same<T, double>::value ||
		std::is_same<T, D3DXVECTOR2>::value ||
		std::is_same<T, D3DXVECTOR3>::value ||
		std::is_same<T, D3DXVECTOR4>::value ||
		std::is_same<T, D3DXCOLOR>::value ||
		std::is_same<T, D3DXMATRIX>::value
	>::type> void Read(T& value)
	{
		in.read(reinterpret_cast<char*>(&value), sizeof(T));
	}

	void Read(std::string& value);
	void Read(std::vector<std::byte>& value);

	const uint ReadUInt()
	{
		uint value = 0;
		Read(value);

		return value;
	}
	//=========================================================

private:
	StreamMode mode;
	std::ifstream in;
	std::ofstream out;
};