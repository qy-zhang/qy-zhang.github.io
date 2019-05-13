import sys
import string
import os
import wave
import pylab as pl
import numpy

def read_wave_data(file_path):
    #open a wave file, and return a Wave_read object
    f = wave.open(file_path,"rb")
    #read the wave's format infomation,and return a tuple
    params = f.getparams()
    #get the info
    nchannels, sampwidth, framerate, nframes = params[:4]
    #Reads and returns nframes of audio, as a string of bytes.
    str_data = f.readframes(nframes)
    #close the stream
    f.close()
    #turn the wave's data to array
    wave_data = numpy.fromstring(str_data, dtype = numpy.short)
    #for the data is stereo,and format is LRLRLR...
    #shape the array to n*2(-1 means fit the y coordinate)
    wave_data.shape = -1, 2
    #transpose the data
    wave_data = wave_data.T
    #calculate the time bar
    time = numpy.arange(0, nframes) * (1.0/framerate)
    return wave_data, time

def main():
    wave_data, time = read_wave_data("E:\Learning\Code\workspace\MAPS_MUS-scn15_11_ENSTDkAm.wav")
    path = 'E:\\Learning\\Code\\workspace\\wav_data.txt'
    f = open(path, "w+")
    for item in wave_data[0]:
        f.write(str(item) + "\n")
    f.close()
    #draw the wave
    # pl.subplot(211)
    # pl.plot(time, wave_data[0])
    # pl.subplot(212)
    # pl.plot(time, wave_data[1], c = "g")
    # pl.show()

if __name__ == "__main__":
    main()