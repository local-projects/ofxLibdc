#pragma once

#include "ofMain.h"
#include <dc1394/dc1394.h>
#include <stdlib.h>
#include <string.h>

// This sets the number of images in the DMA buffer,
// where libdc stores images until you grab them.
#define OFXLIBDC_BUFFER_SIZE 4

namespace ofxLibdc {

class Camera {
public:
	Camera(bool isStereoCamera = false);
	static int getCameraCount();
	
	// pre-setup settings
	void setSize(unsigned int width, unsigned int height);
	void setPosition(unsigned int roiLeft, unsigned int roiTop);
	void setImageType(ofImageType imageType);
	void setFormat7(bool useFormat7, int mode = 0);
	void set1394b(bool use1394b);
	void setBlocking(bool blocking);
    void setBayerMode(dc1394color_filter_t bayerMode, dc1394bayer_method_t method = DC1394_BAYER_METHOD_SIMPLE);
    void disableBayer();
	void setFrameRate(float frameRate);
	
	ofImageType getImageType() const;
	bool getBlocking() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	float getFrameRate() const;
    dc1394framerate_t getFrameRateActual() const;
    
    // stereo camera settings
    void setStereoCamera(bool isStereo);
    bool isStereoCamera() const;
	
	virtual bool setup(int cameraNumber = 0);
	virtual bool setup(string cameraGuid);
	virtual ~Camera();
	
    virtual void close();
    
    // reset bus
    void resetBus( int which = 0 );
    void resetBus( string cameraGuid );
    
	// post-setup settings	
    string getGuid();
	void printFeatures();
    
	// normalized values
	void setBrightness(float brightness);
	void setGamma(float gamma);
	void setGain(float gain);
	void setExposure(float exposure);
	void setShutter(float shutter);
	void setFeature(dc1394feature_t feature, float value);
	
	// absolute values
	void setBrightnessAbs(float brightness);
	void setGammaAbs(float gamma);
	void setGainAbs(float gain);
	void setExposureAbs(float exposure);
	void setShutterAbs(float shutter); // in seconds
	void setFeatureAbs(dc1394feature_t feature, float value);
	
	// raw values
	void setBrightnessRaw(unsigned int brightness);
	void setGammaRaw(unsigned int gamma);
	void setGainRaw(unsigned int gain);
	void setExposureRaw(unsigned int exposure);
	void setShutterRaw(unsigned int shutter);
	void setFeatureRaw(dc1394feature_t feature, unsigned int value);
	
	// normalized values
	float getBrightness() const;
	float getGamma() const;
	float getGain() const;
	float getExposure() const;
	float getShutter() const;
	float getFeature(dc1394feature_t feature) const;
	
	// absolute values
	float getBrightnessAbs() const;
	float getGammaAbs() const;
	float getGainAbs() const;
	float getExposureAbs() const;
	float getShutterAbs() const; // in seconds
	float getFeatureAbs(dc1394feature_t feature) const;
	
	// raw values
	unsigned int getBrightnessRaw() const;
	unsigned int getGammaRaw() const;
	unsigned int getGainRaw() const;
	unsigned int getExposureRaw() const;
	unsigned int getShutterRaw() const;
	unsigned int getFeatureRaw(dc1394feature_t feature) const;
	
	// raw value ranges
	void getBrightnessRawRange(unsigned int* min, unsigned int* max) const;
	void getGammaRawRange(unsigned int* min, unsigned int* max) const;
	void getGainRawRange(unsigned int* min, unsigned int* max) const;
	void getExposureRawRange(unsigned int* min, unsigned int* max) const;
	void getShutterRawRange(unsigned int* min, unsigned int* max) const;
	void getFeatureRawRange(dc1394feature_t feature, unsigned int* min, unsigned int* max) const;
	
	// abs value ranges
	void getBrightnessAbsRange(float* min, float* max) const;
	void getGammaAbsRange(float* min, float* max) const;
	void getGainAbsRange(float* min, float* max) const;
	void getExposureAbsRange(float* min, float* max) const;
	void getShutterAbsRange(float* min, float* max) const; // in seconds
	void getFeatureAbsRange(dc1394feature_t feature, float* min, float* max) const;
	
	void printFeatures() const;
	
	// image grabbing
	
	bool grabStill(ofImage& img);
    bool grabStill(ofImage& img1, ofImage& img2);
	bool grabVideo(ofImage& img, bool dropFrames = true);
    bool grabVideo(ofImage& img1, ofImage& img2, bool dropFrames = true);
	
	void flushBuffer();
	
	dc1394camera_t* getLibdcCamera();
	bool isReady() const;

protected:
	static dc1394_t* libdcContext;
	static int libdcCameras;
	static void startLibdcContext();
	static void stopLibdcContext();
    
    uint64_t cameraGuidInt;
    
    bool isStereo;
    dc1394stereo_method_t stereoMethod;
    dc1394color_coding_t colorCoding;
	
	static ofImageType getOfImageType(dc1394color_coding_t imageType);
	static dc1394color_coding_t getLibdcType(ofImageType imageType);
		
	dc1394camera_t* camera;
	dc1394video_mode_t videoMode;
	dc1394capture_policy_t capturePolicy;
    dc1394framerate_t framerateActual;
	unsigned int width, height, left, top;
	ofImageType imageType;
	float frameRate;
	
	bool useBayer;
    dc1394color_filter_t bayerMode;
    dc1394bayer_method_t bayerMethod;
	
	bool useFormat7;
	int format7Mode;
	bool use1394b;
	bool ready;
	
	bool grabFrame(ofImage& img);
    bool grabFrame(ofImage& img1, ofImage& img2);
	bool initCamera(uint64_t cameraGuid);
	bool applySettings();
	
	void quantizeSize();
	void quantizePosition();
	
	void setTransmit(bool transmit);
	unsigned int getSourceDepth() const;
	
	static string makeString(int name);
	static float makeFloat(int name);
};

}
