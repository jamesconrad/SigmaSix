#include "Audio.h"
#include <uuids.h>

Audio::Audio()
{
	pigb = NULL;
	pimc = NULL;
	pimex = NULL;
	piba = NULL;
	ready = false;
	currentFile = NULL;
}

Audio::~Audio()
{
	Shutdown();
}

void Audio::Shutdown()
{
	if (pimc)
		pimc->Stop();

	if (pigb)
	{
		pigb->Release();
		pigb = NULL;
	}

	if (pimc)
	{
		pimc->Release();
		pimc = NULL;
	}

	if (pimex)
	{
		pimex->Release();
		pimex = NULL;
	}

	if (piba)
	{
		piba->Release();
		piba = NULL;
	}

	ready = false;
}

bool Audio::Load(LPCWSTR szFile)
{
	//Make sure file is not already loaded
	if (currentFile != szFile)
	{
		//Reset
		Shutdown();
		CoInitialize(NULL);
		//Check if properly reset
		if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&this->pigb)))
		{
			//Get handles to required objects
			pigb->QueryInterface(IID_IMediaControl, (void**)&pimc);
			pigb->QueryInterface(IID_IMediaEventEx, (void**)&pimex);
			pigb->QueryInterface(IID_IBasicAudio, (void**)&piba);
			//Check if sucessful
			HRESULT hr = pigb->RenderFile(szFile, NULL);
			if (SUCCEEDED(hr))
			{
				ready = true;
			}
		}
		return ready;
	}
	return ready;
}

bool Audio::Play()
{
	//Start playing music
	if (ready && pimc)
	{
		HRESULT hr = pimc->Run();
		return SUCCEEDED(hr);
	}
	return false;
}

bool Audio::Pause()
{
	//Pause music
	if (ready && pimc)
	{
		HRESULT hr = pimc->Pause();
		return SUCCEEDED(hr);
	}
	return false;
}

bool Audio::Stop()
{
	//Set time to 0, and pause.
	if (ready && pimc)
	{
		HRESULT hr = pimc->Stop();
		return SUCCEEDED(hr);
	}
	return false;
}

bool Audio::SetVolume(long vol)
{
	//Change volume, returns sucesses
	if (ready && piba)
	{
		HRESULT hr = piba->put_Volume(vol);
		return SUCCEEDED(hr);
	}
	return false;
}

long Audio::GetVolume()
{
	//Get volume, returns -1 if not ready
	if (ready && piba)
	{
		long vol = -1;
		HRESULT hr = piba->get_Volume(&vol);
		if (SUCCEEDED(hr))
			return vol;
	}

	return -1;
}