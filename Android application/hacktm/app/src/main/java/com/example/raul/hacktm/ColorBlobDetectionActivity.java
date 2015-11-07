package com.example.raul.hacktm;


import java.io.File;
import java.io.FileDescriptor;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;
import java.util.Vector;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfPoint;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.example.raul.hacktm.R;


enum State {
    born, forward, stop, right,
    left, wait, park
}


public class ColorBlobDetectionActivity extends Activity implements/* OnTouchListener,*/ CvCameraViewListener2, SensorEventListener {
    private static final String TAG = "OCVSample::Activity";
    private State state;
    private boolean mIsColorSelected = false;
    private Mat mRgba;
    private Scalar mBlobColorRgba;
    private Scalar mBlobColorHsv;
    private ColorBlobDetector mDetector;
    private Mat mSpectrum;
    private Size SPECTRUM_SIZE;
    private Scalar CONTOUR_COLOR_RED;
    private Scalar CONTOUR_COLOR_GREEN;
    private Scalar CONTOUR_COLOR_BLUE;
    private Scalar CONTOUR_COLOR_BLACK;
    private double maxArea = -1;
    private int maxAreaIdx = -1;
    private int nrColorFrame = 0;
    private int nrRectangleRed, nrRectangleBlue, nrRectangleGreen;
    private int nrTriangleRed, nrTriangleBlue, nrTriangleGreen;
    private int nrPentagonRed, nrPentagonBlue, nrPentagonGreen;
    private int nrHexagonRed, nrHexagonBlue, nrHexagonGreen;
    private int nrForward;
    private int nrArrowRight, nrArrowLeft;
    private int nrParking;
    private List<MatOfPoint> contours_red;
    private List<MatOfPoint> contours_blue;
    private List<MatOfPoint> contours_green;
    private List<MatOfPoint> contours_white;
    private int MIN_VALUE, MAX_VALUE;
    private int nbPoints;
    private List<Point> points;
    private Point stanga;
    private Point dreapta;
    private Point punct;
    private Point sus;
    private Point jos;
    private Point stanga_sus, stanga_jos;
    private Point dreapta_sus, dreapta_jos;
    private Point point;
    private double mijloc;
    private long sumaX, sumaY;
    private Point circleCenter;
    private int greenFound = 0;
    private boolean stop_color;
    private CameraBridgeViewBase mOpenCvCameraView;
    private SensorManager mSensorManager;
    private Sensor mAccelerometer;
    private Sensor mMagnetometer;
    private float currentDegree = 0f;
    private float x_axys, y_axys, z_axys;
    private float[] mLastAccelerometer = new float[3];
    private float[] mLastMagnetometer = new float[3];
    private boolean mLastAccelerometerSet = false;
    private boolean mLastMagnetometerSet = false;
    private float[] mR = new float[9];
    private float[] mOrientation = new float[3];
    private float mCurrentDegree = 0f;
    private boolean left = false;
    private boolean right = false;
    private boolean left_done = true;
    private boolean right_done = true;
    private float initialRightDegreeRotation = 0f;
    private float initialLeftDegreeRotation = 0f;
    private float difference;
    public MediaRecorder myAudioRecorder;
    private MediaPlayer myPlayer;
    private int nrRecording;
    String outputFile;
    private boolean vocalPlay = false;
    private int start = 0;
    private int i;
    private Scalar color_radius;
    private Scalar white_color_radius;
    private boolean possible_arrow = false;
    private Point blue_center;
    private Point white_center;
    private long nrPixels;
    private long xAxysSum, yAxysSum;
    private boolean possible_parking = false;
    private double y_min, y_max;

    class BTTester {
        private ArrayList<String> mPairedDevicesArrayAdapter;

        private boolean checkBTState() {
            // Check device has Bluetooth and that it is turned on
            BluetoothAdapter mBtAdapter = BluetoothAdapter.getDefaultAdapter(); // CHECK THIS OUT THAT IT WORKS!!!
            if (mBtAdapter == null) {
                Toast.makeText(getBaseContext(), "Device does not support Bluetooth", Toast.LENGTH_SHORT).show();
            } else {
                if (!mBtAdapter.isEnabled()) {
                    //Prompt user to turn on Bluetooth
                    Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                    startActivityForResult(enableBtIntent, 1);
                } else
                    return true;
            }
            return false;
        }

        public ArrayList<String> getDevices() {
            mPairedDevicesArrayAdapter = new ArrayList<String>();
            if (checkBTState()) {

                // Get a set of currently paired devices and append to 'pairedDevices'
                Set<BluetoothDevice> pairedDevices = BluetoothAdapter.getDefaultAdapter().getBondedDevices();

                // Add previosuly paired devices to the array
                if (pairedDevices.size() > 0) {
                    for (BluetoothDevice device : pairedDevices) {
                        mPairedDevicesArrayAdapter.add(device.getName() + "\n" + device.getAddress());
                    }
                } else {
                    mPairedDevicesArrayAdapter.add("null");
                }
            }
            return mPairedDevicesArrayAdapter;
        }

    }

    class BTHandler {

        Button btnOn, btnOff;
        TextView txtArduino, txtString, txtStringLength, sensorView0, sensorView1, sensorView2, sensorView3;
        Handler bluetoothIn;

        final int handlerState = 0;                        //used to identify handler message
        private BluetoothSocket btSocket = null;
        private StringBuilder recDataString = new StringBuilder();

        private ConnectedThread mConnectedThread = null;


        private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
            UUID BTMODULEUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
            return device.createRfcommSocketToServiceRecord(BTMODULEUUID);
        }

        public void socketOpen(String fullDeviceAddress) {
            //Get the MAC address from the DeviceListActivty via EXTRA
            String address = fullDeviceAddress.substring(fullDeviceAddress.length() - 17);

            //create device and set the MAC address
            BluetoothDevice device = BluetoothAdapter.getDefaultAdapter().getRemoteDevice(address);

            try {
                btSocket = createBluetoothSocket(device);
            } catch (IOException e) {
                //  Toast.makeText(getBaseContext(), "Socket creation failed", Toast.LENGTH_LONG).show();
            }
            try {
                btSocket.connect();
            } catch (IOException e) {
                // Toast.makeText(getBaseContext(), "Socket connect failed", Toast.LENGTH_LONG).show();
                socketClose();
            }
            mConnectedThread = new ConnectedThread(btSocket);
            mConnectedThread.start();
        }

        public void socketWrite(String mess) {
            if (mConnectedThread != null)
                mConnectedThread.write(mess);
        }

        public void socketClose() {
            try {
                btSocket.close();
            } catch (IOException e2) {
                // Toast.makeText(getBaseContext(), "Socket close failed", Toast.LENGTH_LONG).show();
            }
        }

        //create new class for connect thread
        private class ConnectedThread extends Thread {
            private final InputStream mmInStream;
            private final OutputStream mmOutStream;

            //creation of the connect thread
            public ConnectedThread(BluetoothSocket socket) {
                OutputStream tmpOut = null;
                InputStream tmpIn = null;
                try {
                    //Create I/O streams for connection
                    tmpIn = socket.getInputStream();
                    tmpOut = socket.getOutputStream();
                } catch (IOException e) {
                    Toast.makeText(getBaseContext(), "Error opening streams", Toast.LENGTH_LONG).show();
                }
                mmInStream = tmpIn;
                mmOutStream = tmpOut;
            }


            //write method
            public void write(String input) {
                byte[] msgBuffer = input.getBytes();           //converts entered String into bytes
                try {
                    mmOutStream.write(msgBuffer);                //write bytes over BT connection via outstream
                    mmOutStream.flush();
                } catch (IOException e) {
                    //if you cannot write, close the application
                    //Toast.makeText(getBaseContext(), "Connection Failure", Toast.LENGTH_LONG).show();
                }
            }


        }
    }

    private static String deviceName = "RN-42";
    private static volatile String s = "born";
    private static String path;

    private static ColorBlobDetectionActivity color;
    BluetoothAdapter mBluetoothAdapter;
    private BluetoothSocket socket = null;
    private OutputStream mmOutStream = null;
    private BTHandler bth = null;
    protected final BroadcastReceiver mReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();

            if (action.equals(BluetoothAdapter.ACTION_STATE_CHANGED)) {
                final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE,
                        BluetoothAdapter.ERROR);
                switch (state) {
                    case BluetoothAdapter.STATE_OFF:
                        processBluetoothChange("no tooth");
                        break;
                    case BluetoothAdapter.STATE_TURNING_OFF:
                        processBluetoothChange("no tooth");
                        break;
                    case BluetoothAdapter.STATE_ON:
                        processBluetoothChange("born");
                        break;
                    case BluetoothAdapter.STATE_TURNING_ON:
                        processBluetoothChange("born");
                        break;
                }
            }
        }
    };

    public void processBluetoothChange(String newstate) {
        processFSMState(newstate);
    }

    Runnable fsm = new Runnable() {

        private void exit() {
            color.runOnUiThread(new Runnable() {
                public void run() {

                    finish();
                    Intent intent = new Intent(ColorBlobDetectionActivity.this, Controller.class);
                    startActivity(intent);
                }
            });

        }

        @Override
        public void run() {
            String state = s;
            char command;
            int i = 0, status = 1;
            int delayDefault = 30, delayBreak = -1;
            state = "born";
            while (true && stop_color != true) {
                try {
                    Thread.sleep(50);
                    switch (state) {
                        case "no tooth":

                            if (bth != null) {
                                bth.socketClose();
                            }
                            break;
                        case "born":
                            BTTester btt = new BTTester();
                            delayDefault = 9;
                            bth = new BTHandler();
                            ArrayList<String> listOfDevices = btt.getDevices();
                            if (listOfDevices.size() != 0) {
                                //search for bn
                                for (String fullName : listOfDevices) {
                                    if (fullName.indexOf(deviceName) != -1) {
                                        deviceName = fullName;
                                        break;
                                    }
                                }
                                bth.socketOpen(deviceName);
                                state = "";
                                Log.e("Raul","born");
                            } else {
                                state = "no tooth";
                            }

                            break;

                        case "forward":
                            if (bth.btSocket != null)
                                bth.socketWrite("8");
                            state = "";
                            Log.e("Raul","forward");
                            break;
                        case "stop":
                            if (bth.btSocket != null)
                                bth.socketWrite("5");
                            state = "";
                            Log.e("Raul","stop");
                            break;
                        case "left":
                            if (bth.btSocket != null) {
                                bth.socketWrite("4");
                                left = true;
                                Log.e("Raul","left");
                            }
                            state = "";
                            break;
                        case "right":
                            if (bth.btSocket != null) {
                                right = true;
                                bth.socketWrite("6");
                                Log.e("Raul", "right");
                            }
                            state = "";
                            break;
                        case "park":
                            if (bth.btSocket != null) {
                                right = true;
                                bth.socketWrite("8");
                                Log.e("Raul", "park");
                            }
                            state = "";
                            break;
                        default:
                            state = "";
                            break;


                    }
                } catch (InterruptedException e) {
                    //check if the user isn't keeping the button pressed before setting state
                    //if user presses multiuple buttons stop car, end bluetooth comm and set state to default
                    state = s;
                }
            }
        }

    };
    private Thread t = null;

    public String getS() {
        return s;
    }

    public void setS(String par) {
        s = par;
    }

    public void processFSMState(CharSequence text) {
        setS(text.toString());
        if (t != null) {
            t.interrupt();
        }

    }


    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS: {
                    Log.i(TAG, "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                    // mOpenCvCameraView.setOnTouchListener(ColorBlobDetectionActivity.this);
                }
                break;
                default: {
                    super.onManagerConnected(status);
                }
                break;
            }
        }
    };

    public ColorBlobDetectionActivity() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }

    /**
     * Called when the activity is first created.
     */

    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        try {
            Thread.sleep(500);
            Log.e("Raul","Am dormit 500");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        nrRecording = 0;
        mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mMagnetometer = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

        myAudioRecorder = new MediaRecorder();
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        stop_color = false;
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.color_blob_detection_surface_view);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.color_blob_detection_activity_surface_view);
        mOpenCvCameraView.setCvCameraViewListener(this);

        Button reset_button = (Button) findViewById(R.id.reset_button);
        reset_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                for (i = 1; i <= nrRecording; i++) {
                    outputFile = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recording" + Integer.toString(i) + ".mp3";
                    File file = new File(outputFile);
                    boolean deleted = file.delete();

                }
                nrRecording = 0;
                if (myPlayer != null) {
                    myPlayer.stop();
                    myPlayer.release();
                    myPlayer = null;
                }

            }
        });


        Button record_button = (Button) findViewById(R.id.record_button);

        record_button.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {

                    case MotionEvent.ACTION_DOWN:


                        myAudioRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
                        myAudioRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
                        myAudioRecorder.setAudioEncoder(MediaRecorder.OutputFormat.AMR_NB);
                        ;

                        try {
                            nrRecording++;
                            outputFile = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recording" + String.valueOf(nrRecording) + ".mp3";
                            myAudioRecorder.setOutputFile(outputFile);
                            myAudioRecorder.prepare();
                            myAudioRecorder.start();

                        } catch (IllegalStateException e) {
                            // TODO Auto-generated catch block
                            e.printStackTrace();
                        } catch (IOException e) {
                            // TODO Auto-generated catch block
                            e.printStackTrace();
                        }
                        return true;
                    case MotionEvent.ACTION_UP:
                        try {
                            myAudioRecorder.stop();
                        } catch (RuntimeException e) {
                            myAudioRecorder.reset();
                        }
                        return true;
                    default:
                        return false;


                }

            }
        });

        Button button = (Button) findViewById(R.id.return_button);
        button.setOnClickListener(new View.OnClickListener() {

                                      @Override
                                      public void onClick(View view) {
                                          bth.socketClose();
                                          finish();
                                          Intent intent = new Intent(ColorBlobDetectionActivity.this, Controller.class);
                                          startActivity(intent);


                                      }
                                  }
        );
        t = new Thread(fsm);
        t.start();
    }

    @Override
    public void onPause() {
        super.onPause();
        int i;
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
        mSensorManager.unregisterListener(this, mAccelerometer);
        mSensorManager.unregisterListener(this, mMagnetometer);
        for (i = 1; i <= nrRecording; i++) {
            outputFile = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recording" + Integer.toString(i) + ".mp3";
            File file = new File(outputFile);
            boolean deleted = file.delete();
        }
        if (myPlayer != null) {
            myPlayer.stop();
            myPlayer.release();
            myPlayer = null;
        }
        if (myAudioRecorder != null) {
            myAudioRecorder.release();
            myAudioRecorder = null;
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor == mAccelerometer) {
            System.arraycopy(event.values, 0, mLastAccelerometer, 0, event.values.length);
            mLastAccelerometerSet = true;
        } else if (event.sensor == mMagnetometer) {
            System.arraycopy(event.values, 0, mLastMagnetometer, 0, event.values.length);
            mLastMagnetometerSet = true;
        }
        if (mLastAccelerometerSet && mLastMagnetometerSet) {
            SensorManager.getRotationMatrix(mR, null, mLastAccelerometer, mLastMagnetometer);
            SensorManager.getOrientation(mR, mOrientation);
            float azimuthInRadians = mOrientation[0];
            float azimuthInDegress = (float) (Math.toDegrees(azimuthInRadians) + 360) % 360;

            mCurrentDegree = azimuthInDegress;
            if (right == true) {
                initialRightDegreeRotation = mCurrentDegree;
                right = false;
                right_done = false;
            }
            if (initialRightDegreeRotation != 0) {
                if ((initialRightDegreeRotation + 90 < 360) && (initialRightDegreeRotation + 90 < mCurrentDegree)) {

                    initialRightDegreeRotation = 0;
                    right_done = true;
                    processFSMState("forward");

                } else {
                    difference = (90 + initialLeftDegreeRotation)%360;
                    if ((mCurrentDegree < difference + 2) && (mCurrentDegree > difference - 2)) {
                        initialRightDegreeRotation = 0;
                        right_done = true;
                        processFSMState("forward");
                    }

                }
            }


            if (left == true) {
                initialLeftDegreeRotation = mCurrentDegree;
                left = false;
                left_done = false;
            }
            if (initialLeftDegreeRotation != 0) {
                if (initialLeftDegreeRotation - 90 >= 0) {
                    if (mCurrentDegree < initialLeftDegreeRotation - 90) {
                        initialLeftDegreeRotation = 0;
                        left_done = true;
                        processFSMState("forward");
                    } else {
                        // keep rotating
                    }
                } else {
                    difference = 270 + initialLeftDegreeRotation;
                    if ((mCurrentDegree < difference + 2) && (mCurrentDegree > difference - 2)) {
                        initialLeftDegreeRotation = 0;
                        left_done = true;
                        processFSMState("forward");
                    }

                }
            }

        }
    }

    @Override
    public void onResume() {
        super.onResume();
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
        mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_GAME);
        mSensorManager.registerListener(this, mMagnetometer, SensorManager.SENSOR_DELAY_GAME);
    }

    public void onDestroy() {
        super.onDestroy();
        int i;
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
        stop_color = true;
        if (bth.btSocket != null) {
            //  bth.socketWrite("5");
            bth.socketClose();
        }
        mSensorManager.unregisterListener(this, mAccelerometer);
        mSensorManager.unregisterListener(this, mMagnetometer);
        if (myPlayer != null) {
            myPlayer.stop();
            myPlayer.release();
            myPlayer = null;
        }
        if (myAudioRecorder != null) {
            myAudioRecorder.release();
            myAudioRecorder = null;
        }
        for (i = 1; i <= nrRecording; i++) {
            outputFile = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recording" + Integer.toString(i) + ".mp3";
            File file = new File(outputFile);
            boolean deleted = file.delete();
        }

    }

    public void onCameraViewStarted(int width, int height) {
        mRgba = new Mat(height, width, CvType.CV_8UC4);
        mDetector = new ColorBlobDetector();
        mSpectrum = new Mat();
        mBlobColorRgba = new Scalar(255);
        mBlobColorHsv = new Scalar(255);
        SPECTRUM_SIZE = new Size(200, 64);
        CONTOUR_COLOR_RED = new Scalar(255, 0, 0, 255);
        CONTOUR_COLOR_BLUE = new Scalar(0, 0, 255, 255);
        CONTOUR_COLOR_GREEN = new Scalar(0, 255, 0, 255);
        CONTOUR_COLOR_BLACK = new Scalar(255, 255, 0, 255);
        circleCenter = new Point();
        color_radius = new Scalar(20, 60, 82);
        white_color_radius = new Scalar(90, 50, 40);
        state = state.born;
        white_center = new Point();
        blue_center = new Point();
    }

    public void onCameraViewStopped() {
        mRgba.release();
    }

    /*
        public boolean onTouch(View v, MotionEvent event) {
            int cols = mRgba.cols();
            int rows = mRgba.rows();

            int xOffset = (mOpenCvCameraView.getWidth() - cols) / 2;
            int yOffset = (mOpenCvCameraView.getHeight() - rows) / 2;

            int x = (int) event.getX() - xOffset;
            int y = (int) event.getY() - yOffset;

            Log.i(TAG, "Touch image coordinates: (" + x + ", " + y + ")");

            if ((x < 0) || (y < 0) || (x > cols) || (y > rows)) return false;

            Rect touchedRect = new Rect();

            touchedRect.x = (x > 4) ? x - 4 : 0;
            touchedRect.y = (y > 4) ? y - 4 : 0;

            touchedRect.width = (x + 4 < cols) ? x + 4 - touchedRect.x : cols - touchedRect.x;
            touchedRect.height = (y + 4 < rows) ? y + 4 - touchedRect.y : rows - touchedRect.y;

            Mat touchedRegionRgba = mRgba.submat(touchedRect);

            Mat touchedRegionHsv = new Mat();
            Imgproc.cvtColor(touchedRegionRgba, touchedRegionHsv, Imgproc.COLOR_RGB2HSV_FULL);

            // Calculate average color of touched region
            mBlobColorHsv = Core.sumElems(touchedRegionHsv);
            int pointCount = touchedRect.width * touchedRect.height;
            for (int i = 0; i < mBlobColorHsv.val.length; i++)
                mBlobColorHsv.val[i] /= pointCount;

            mBlobColorRgba = converScalarHsv2Rgba(mBlobColorHsv);

            Log.i(TAG, "Touched rgba color: (" + mBlobColorRgba.val[0] + ", " + mBlobColorRgba.val[1] +
                    ", " + mBlobColorRgba.val[2] + ", " + mBlobColorRgba.val[3] + ")");

            mDetector.setHsvColor(mBlobColorHsv);

            Imgproc.resize(mDetector.getSpectrum(), mSpectrum, SPECTRUM_SIZE);

            mIsColorSelected = true;

            touchedRegionRgba.release();
            touchedRegionHsv.release();

            return false; // don't need subsequent touch events
        }

    */


    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
        //Core.putText(mRgba, "", new Point(1, 250), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 0, 0), 2);
        // Core.putText(mRgba, "Mai este de rotit: "+String.valueOf((initialLeftDegreeRotation + 90)%360- mCurrentDegree), new Point(1, 150), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(255, 255, 255, 255), 2);
        nrColorFrame++;


        if (nrColorFrame == 3) {
            nrColorFrame = 0;
            MatOfPoint thisContour;
            MatOfPoint2f thisContour2f = new MatOfPoint2f();
            MatOfPoint approxContour = new MatOfPoint();
            MatOfPoint2f approxContour2f = new MatOfPoint2f();

            List<MatOfPoint> contourTemp = new ArrayList();

            mBlobColorHsv.val[0] = 90;
            mBlobColorHsv.val[1] = 50;
            mBlobColorHsv.val[2] = 215;
            mDetector.setColorRadius(white_color_radius);
            mDetector.setHsvColor(mBlobColorHsv);
            mDetector.process(mRgba);
            contours_white = mDetector.getContours();


            for (int idx = 0; idx < contours_white.size(); idx++) {

                thisContour = contours_white.get(idx);
                thisContour.convertTo(thisContour2f, CvType.CV_32FC2);


                Imgproc.approxPolyDP(thisContour2f, approxContour2f, 0.07 * Imgproc.arcLength(thisContour2f, true), true);

                approxContour2f.convertTo(approxContour, CvType.CV_32S);


                contourTemp.add(approxContour);
                Imgproc.drawContours(mRgba, contourTemp, -1, CONTOUR_COLOR_BLACK);

                if (possible_arrow == true) {
                    points = approxContour.toList();
                    nrPixels = 0;
                    xAxysSum = 0;
                    yAxysSum = 0;
                    for (Point p : points) {
                        nrPixels++;
                        xAxysSum += p.x;
                        yAxysSum += p.y;
                    }

                    white_center.x = xAxysSum;
                    white_center.y = yAxysSum;


                    if ((approxContour.size().height == 4) && (white_center.x - blue_center.x < 300 && white_center.x - blue_center.x > -300)
                            && (white_center.y - blue_center.y < 300 && white_center.y - blue_center.y > -300)) {

                        points = approxContour.toList();

                        stanga = new Point(999, 999);
                        dreapta = new Point(-1, 999);
                        sus = new Point(999, 999);
                        jos = new Point(999, -1);
                        for (Point p : points) {
                            if (stanga.x > p.x) {
                                stanga.x = p.x;
                                stanga.y = p.y;
                            }
                            if (dreapta.x < p.x) {
                                dreapta.x = p.x;
                                dreapta.y = p.y;

                            }
                            if (sus.y > p.y) {
                                sus.y = p.y;
                                sus.x = p.x;

                            }
                            if (jos.y < p.y) {
                                jos.y = p.y;
                                jos.x = p.x;

                            }

                        }
                        if (sus.x < (dreapta.x + stanga.x) / 2 && jos.x < (dreapta.x + stanga.x) / 2) {
                            nrArrowLeft++;


                        } else if (sus.x > (dreapta.x + stanga.x) / 2 && jos.x > (dreapta.x + stanga.x) / 2) {
                            nrArrowRight++;

                        }


                    }


                }
                if (possible_parking == true) {
                    points = approxContour.toList();
                    nrPixels = 0;
                    xAxysSum = 0;
                    yAxysSum = 0;
                    for (Point p : points) {
                        nrPixels++;
                        xAxysSum += p.x;
                        yAxysSum += p.y;
                    }

                    white_center.x = xAxysSum;
                    white_center.y = yAxysSum;


                    if (approxContour.size().height == 6 && white_center.x - blue_center.x < 200 && (white_center.x - blue_center.x > -200)
                            && (white_center.y - blue_center.y < 500 && white_center.y - blue_center.y > -500)) {

                      /*  points = approxContour.toList();

                        stanga_sus = new Point(999, 999);
                        stanga_jos = new Point(999, -1);
                        dreapta_sus = new Point(-1, 999);
                        dreapta_jos = new Point(-1, -1);

                        for(Point p:points){
                            if(stanga_sus.x >= p.x && stanga_sus.y >= p.y) {
                                stanga_sus.x = p.x;
                                stanga_sus.y = p.y;
                            }
                            if(dreapta_sus.x <= p.x && dreapta_sus.y >= p.y){
                                dreapta_sus.x = p.x;
                                dreapta_sus.y = p.y;
                            }
                            if(stanga_jos.x >= p.x && stanga_jos.y <= p.y){
                                stanga_jos.x = p.x;
                                stanga_jos.y = p.y;
                            }
                            if(dreapta_jos.x <= p.x && dreapta_jos.y <= p.y){
                                dreapta_jos.x = p.x;
                                dreapta_jos.y = p.y;
                            }
                        }*/
                        // if((dreapta_sus.x - stanga_sus.x) > (dreapta_jos.x - stanga_jos.x)){
                        nrParking++;
                        possible_parking = false;
                        //  }

                    }

                }
            }
        } else if (nrColorFrame == 1) {

            mRgba = inputFrame.rgba();
            //mBlobColorRgba=();
            String mesaj1, mesaj_red, mesaj_green, mesaj_blue;

            MatOfPoint thisContour;
            MatOfPoint2f thisContour2f = new MatOfPoint2f();
            MatOfPoint approxContour = new MatOfPoint();
            MatOfPoint2f approxContour2f = new MatOfPoint2f();

            List<MatOfPoint> contourTemp = new ArrayList();


            mBlobColorHsv.val[0] = 20;
            mBlobColorHsv.val[1] = 160;
            mBlobColorHsv.val[2] = 172;

            mDetector.setColorRadius(color_radius);
            mDetector.setHsvColor(mBlobColorHsv);
            mDetector.process(mRgba);
            contours_red = mDetector.getContours();


            //   mDetector.process(mRgba);
            //red shape
            if (contours_red.size() == 2)
                vocalPlay = true;
            if (contours_red.size() == 1) {

                for (int idx = 0; idx < contours_red.size(); idx++) {

                    thisContour = contours_red.get(idx);
                    thisContour.convertTo(thisContour2f, CvType.CV_32FC2);


                    Imgproc.approxPolyDP(thisContour2f, approxContour2f, 0.04 * Imgproc.arcLength(thisContour2f, true), true);

                    approxContour2f.convertTo(approxContour, CvType.CV_32S);


                    contourTemp.add(approxContour);
                    Imgproc.drawContours(mRgba, contourTemp, -1, CONTOUR_COLOR_RED);


                    if (approxContour.size().height > 6) {
                        nrHexagonRed++;
                    }

                }
            }


            Mat colorLabel = mRgba.submat(4, 68, 4, 68);
            colorLabel.setTo(mBlobColorRgba);
            Mat spectrumLabel = mRgba.submat(4, 4 + mSpectrum.rows(), 70, 70 + mSpectrum.cols());
            mSpectrum.copyTo(spectrumLabel);


        } /*else if (nrColorFrame == 3) {
            mRgba = inputFrame.rgba();
            //mBlobColorRgba=();
            MatOfPoint thisContour;
            MatOfPoint2f thisContour2f = new MatOfPoint2f();
            MatOfPoint approxContour = new MatOfPoint();
            MatOfPoint2f approxContour2f = new MatOfPoint2f();

            List<MatOfPoint> contourTemp = new ArrayList();


            mBlobColorHsv.val[0] = 120;
            mBlobColorHsv.val[1] = 255;
            mBlobColorHsv.val[2] = 80;
            mDetector.setColorRadius(color_radius);
            mDetector.setHsvColor(mBlobColorHsv);
            mDetector.process(mRgba);
            contours_green = mDetector.getContours();


            if (contours_green.size() == 1) {

                for (int idx = 0; idx < contours_green.size(); idx++) {

                    thisContour = contours_green.get(idx);
                    thisContour.convertTo(thisContour2f, CvType.CV_32FC2);


                    Imgproc.approxPolyDP(thisContour2f, approxContour2f, 0.04 * Imgproc.arcLength(thisContour2f, true), true);

                    approxContour2f.convertTo(approxContour, CvType.CV_32S);


                    contourTemp.add(approxContour);
                    Imgproc.drawContours(mRgba, contourTemp, -1, CONTOUR_COLOR_GREEN);

                    if (approxContour.size().height > 5) {
                        nrForward++;
                    }

                }

                Mat colorLabel = mRgba.submat(4, 68, 4, 68);
                colorLabel.setTo(mBlobColorRgba);
                Mat spectrumLabel = mRgba.submat(4, 4 + mSpectrum.rows(), 70, 70 + mSpectrum.cols());
                mSpectrum.copyTo(spectrumLabel);

            }

        //blue
        }*/ else if (nrColorFrame == 2) {

            mRgba = inputFrame.rgba();
            //mBlobColorRgba=();
            String mesaj1, mesaj_red, mesaj_green, mesaj_blue;

            MatOfPoint thisContour;
            MatOfPoint2f thisContour2f = new MatOfPoint2f();
            MatOfPoint approxContour = new MatOfPoint();
            MatOfPoint2f approxContour2f = new MatOfPoint2f();

            List<MatOfPoint> contourTemp = new ArrayList();
            mBlobColorHsv.val[0] = 150;
            mBlobColorHsv.val[1] = 160;
            mBlobColorHsv.val[2] = 172;

            mDetector.setColorRadius(color_radius);
            mDetector.setHsvColor(mBlobColorHsv);
            mDetector.process(mRgba);
            contours_blue = mDetector.getContours();

            if (vocalPlay == true) {

                vocalPlay = false;

                start++;

                if (start <= 1) {
                    try {
                        myPlayer = new MediaPlayer();
                        outputFile = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recording" + Integer.toString(contours_blue.size()) + ".mp3";
                        ;
                        File f = new File(outputFile);
                        if (f.exists() && !f.isDirectory()) {

                            myPlayer.setDataSource(outputFile);
                            try {
                                myPlayer.prepare();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            myPlayer.start();
                            myPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {

                                public void onCompletion(MediaPlayer mp) {
                                    myPlayer.stop();
                                    myPlayer.release();
                                    myPlayer = null;
                                    Log.i("Completion Listener", "Song Complete");
                                }
                            });
                        }

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (start > 1) {
                    if (myPlayer == null) {

                        try {
                            myPlayer = new MediaPlayer();
                            outputFile = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recording" + Integer.toString(contours_blue.size()) + ".mp3";
                            ;
                            File f = new File(outputFile);
                            if (f.exists() && !f.isDirectory()) {

                                myPlayer.setDataSource(outputFile);
                                try {
                                    myPlayer.prepare();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                myPlayer.start();
                                myPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {

                                    public void onCompletion(MediaPlayer mp) {
                                        myPlayer.stop();
                                        myPlayer.release();
                                        myPlayer = null;
                                        Log.i("Completion Listener", "Song Complete");
                                    }
                                });
                            }

                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }

            // if (contours_blue.size() == 1) {

            for (int idx = 0; idx < contours_blue.size(); idx++) {

                thisContour = contours_blue.get(idx);
                double contourArea = Imgproc.contourArea(thisContour);
                thisContour.convertTo(thisContour2f, CvType.CV_32FC2);


                Imgproc.approxPolyDP(thisContour2f, approxContour2f, 0.04 * Imgproc.arcLength(thisContour2f, true), true);

                approxContour2f.convertTo(approxContour, CvType.CV_32S);


                contourTemp.add(approxContour);
                Imgproc.drawContours(mRgba, contourTemp, -1, CONTOUR_COLOR_BLUE);

               /* if (approxContour.size().height > 5) {
                    possible_arrow = true;
                    points = approxContour.toList();
                    nrPixels = 0;
                    xAxysSum = 0;
                    yAxysSum = 0;
                    for (Point p : points) {
                        nrPixels++;
                        xAxysSum += p.x;
                        yAxysSum += p.y;
                    }

                    blue_center.x = xAxysSum;
                    blue_center.y = yAxysSum;
                }
                /*if (approxContour.size().height == 4 && contourArea > 2000) {
                   /*possible_parking = true;
                    points = approxContour.toList();
                    nrPixels = 0;
                    xAxysSum = 0;
                    yAxysSum = 0;
                    for (Point p : points) {
                        nrPixels++;
                        xAxysSum += p.x;
                        yAxysSum += p.y;
                    }

                    blue_center.x = xAxysSum;
                    blue_center.y = yAxysSum;*/
                // nrParking++;
                //}
                if (approxContour.size().height > 5) {
                    points = approxContour.toList();

                    stanga = new Point(999, 999);
                    dreapta = new Point(-1, 999);
                    sus = new Point(999, 999);
                    jos = new Point(999, -1);
                    for (Point p : points) {
                        if (stanga.x > p.x) {
                            stanga.x = p.x;
                            stanga.y = p.y;
                        }
                        if (dreapta.x < p.x) {
                            dreapta.x = p.x;
                            dreapta.y = p.y;

                        }
                        if (sus.y > p.y) {
                            sus.y = p.y;
                            sus.x = p.x;

                        }
                        if (jos.y < p.y) {
                            jos.y = p.y;
                            jos.x = p.x;

                        }

                    }
                    if (sus.x < (dreapta.x + stanga.x) / 2 && jos.x < (dreapta.x + stanga.x) / 2) {
                        nrArrowLeft++;


                    } else if (sus.x > (dreapta.x + stanga.x) / 2 && jos.x > (dreapta.x + stanga.x) / 2) {
                        nrArrowRight++;

                    }
                }
            }
            // }


            Mat colorLabel = mRgba.submat(4, 68, 4, 68);
            colorLabel.setTo(mBlobColorRgba);
            Mat spectrumLabel = mRgba.submat(4, 4 + mSpectrum.rows(), 70, 70 + mSpectrum.cols());
            mSpectrum.copyTo(spectrumLabel);
        }

        //WHITE
        if (nrArrowLeft > 6) {
            nrForward = 0;
            nrRectangleRed = 0;
            nrPentagonRed = 0;
            nrHexagonRed = 0;
            nrTriangleRed = 0;
            nrArrowLeft = 0;
            nrArrowRight = 0;
            state = state.left;
            nrParking = 0;
        }
        if (nrArrowRight > 6) {
            nrForward = 0;
            nrRectangleRed = 0;
            nrPentagonRed = 0;
            nrHexagonRed = 0;
            nrTriangleRed = 0;
            nrArrowLeft = 0;
            nrArrowRight = 0;
            state = state.right;
            nrParking = 0;
        }
        //RED

        if (nrHexagonRed > 6) {
            nrForward = 0;
            nrRectangleRed = 0;
            nrPentagonRed = 0;
            nrHexagonRed = 0;
            nrTriangleRed = 0;
            nrArrowLeft = 0;
            nrArrowRight = 0;
            state = state.stop;
            nrParking = 0;
        }

        //BLUE


        //GREEN


        if (nrForward > 6) {
            nrForward = 0;
            nrRectangleGreen = 0;
            nrPentagonGreen = 0;
            nrHexagonGreen = 0;
            nrTriangleGreen = 0;
            nrArrowLeft = 0;
            nrArrowRight = 0;
            state = state.forward;
            nrParking = 0;

        }

        //PARKING
        if (nrParking > 6) {
            nrForward = 0;
            nrRectangleGreen = 0;
            nrPentagonGreen = 0;
            nrHexagonGreen = 0;
            nrTriangleGreen = 0;
            nrArrowLeft = 0;
            nrArrowRight = 0;
            state = state.park;
            possible_parking = false;
        }

        switch (state) {
            case wait:
                break;
            case forward:
                Core.putText(mRgba, "", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 0, 0), 2);
                Core.putText(mRgba, "Forward", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 255, 0, 255), 2);
                processFSMState("forward");
                state = state.wait;
                break;
            case stop:
                processFSMState("stop");
                Core.putText(mRgba, "", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 0, 0), 2);
                Core.putText(mRgba, "Stop", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(255, 0, 0, 255), 2);
                state = state.wait;
                break;
            case left:
                processFSMState("left");
                Core.putText(mRgba, "", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 0, 0), 2);
                Core.putText(mRgba, "Left", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 255, 255), 2);
                state = state.wait;


                break;
            case right:
                processFSMState("right");
                Core.putText(mRgba, "", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 0, 0), 2);
                Core.putText(mRgba, "Right", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 255, 255), 2);
                state = state.wait;


                break;
            case park:
                processFSMState("park");
                Core.putText(mRgba, "", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 0, 0), 2);
                Core.putText(mRgba, "Parking", new Point(1, 230), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(0, 0, 255, 255), 2);
                state = state.wait;
            default:
                break;

        }
        //Core.putText(mRgba, "Unghiul curent: "+mCurrentDegree, new Point(1, 150), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.4, new Scalar(255, 255, 255, 255), 2);

        // Core.putText(mRgba, "Unghiul curent: " + String.valueOf(mCurrentDegree), new Point(1, 150), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.8, new Scalar(0, 0, 0, 0), 2);
        // Core.putText(mRgba, "Numar de fisiere: " + String.valueOf(nrRecording), new Point(1, 180), 3/* CV_FONT_HERSHEY_COMPLEX */, 0.8, new Scalar(0, 0, 0, 0), 2);

        return mRgba;
    }

    private Scalar converScalarHsv2Rgba(Scalar hsvColor) {
        Mat pointMatRgba = new Mat();
        Mat pointMatHsv = new Mat(1, 1, CvType.CV_8UC3, hsvColor);
        Imgproc.cvtColor(pointMatHsv, pointMatRgba, Imgproc.COLOR_HSV2RGB_FULL, 4);

        return new Scalar(pointMatRgba.get(0, 0));
    }

    private Scalar converScalarRgba2Hsv(Scalar rgbaColor) {
        Mat pointMatRgba = new Mat();
        Mat pointMatHsv = new Mat(1, 1, CvType.CV_8UC3, rgbaColor);
        Imgproc.cvtColor(pointMatHsv, pointMatRgba, Imgproc.COLOR_RGB2HSV_FULL);

        return new Scalar(pointMatHsv.get(0, 0));
    }
}
