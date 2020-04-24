#
/*
 *    Copyright (C)  2009, 2010, 2011
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    DAB library is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    DAB library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with DAB library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __AUDIOCARD_DRIVER__
#define __AUDIOCARD_DRIVER__

#include	<string>
#include	<portaudio.h>
#include	<stdio.h>
#include	"ringbuffer.h"
#include	<string>
#include	"output-driver.h"

class	soundcardDriver  : public outputDriver {
public:
	                soundcardDriver		(int16_t, std::string);
			~soundcardDriver	(void);
	void		stop			(void);
	void		restart			(void);
	bool		selectDevice		(const std::string);
	bool		selectDefaultDevice	(void);
	void		sendSample		(std::complex<float>);
private:
	int16_t		numberofDevices		(void);
const	char		*outputChannelwithRate	(int16_t, int32_t);
	int16_t		invalidDevice		(void);
	bool		isValidDevice		(int16_t);
	int32_t		cardRate		(void);

	bool		OutputrateIsSupported	(int16_t, int32_t);
	int32_t		CardRate;
	int16_t		latency;
	int32_t		size;
	bool		portAudio;
	bool		writerRunning;
	int16_t		numofDevices;
	int		paCallbackReturn;
	int16_t		bufSize;
	PaStream	*ostream;
	RingBuffer<float>	*_O_Buffer;
	PaStreamParameters	outputParameters;

	int16_t		*outTable;
protected:
static	int		paCallback_o	(const void	*input,
	                                 void		*output,
	                                 unsigned long	framesperBuffer,
	                                 const PaStreamCallbackTimeInfo *timeInfo,
					 PaStreamCallbackFlags statusFlags,
	                                 void		*userData);
};

#endif
