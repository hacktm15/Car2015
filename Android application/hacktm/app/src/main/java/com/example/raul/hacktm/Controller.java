package com.example.raul.hacktm;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;


import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.os.Handler;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.raul.hacktm.R;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;


public class Controller extends Activity {
    Bitmap bitMap;
    static int TAKE_PICTURE = 1;

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
                Toast.makeText(getBaseContext(), "Socket creation failed", Toast.LENGTH_LONG).show();
            }
            try {
                btSocket.connect();
            } catch (IOException e) {
                Toast.makeText(getBaseContext(), "Socket connect failed", Toast.LENGTH_LONG).show();
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
                Toast.makeText(getBaseContext(), "Socket close failed", Toast.LENGTH_LONG).show();
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

            public void run() {
                byte[] buffer = new byte[1];

                String x;
                int type;
                int data;
                int reception;
                String send;
                // Keep looping to listen for received messages
                while (true) {
                    /*try {
                        StringBuilder mess=new StringBuilder("");

                        while( mmInStream.read(buffer,0,256)!=-1){
                            for(int i=0;i<buffer.length;i++) {
                                if(buffer[i]!=0) {
                                    String ascii="";
                                    switch(Byte.toString(buffer[i])){
                                        case "70":
                                            ascii="F";
                                            break;
                                        case "82":
                                            ascii="R";
                                            break;
                                        case "76":
                                            ascii="L";
                                            break;
                                        case "66":
                                            ascii="B";
                                            break;
                                        case "68":
                                            ascii="D";
                                            break;
                                        case "90":
                                            ascii="Z";
                                            i=buffer.length;
                                            break;
                                        default:
                                            ascii = Byte.toString(buffer[i]);
                                    }
                                    mess.append (ascii+",");
                                }

                            }
                            String finalMess=mess.toString();
                           if(finalMess.indexOf("F")!=-1){
                                finalMess=finalMess.substring(finalMess.indexOf("F"));
                                if(finalMess.indexOf("Z")!=-1){
                                    finalMess=finalMess.substring(0,finalMess.indexOf("Z"));
                                    String[] all=finalMess.split(",");
                                    if(all[all.length-1].equals("D")){
                                        all[all.length-1]="Stopped";
                                    }else{
                                        all[all.length-1]=all[all.length-1]+"%";
                                    }
                                }
                            }
                            mess.setLength(0);
                        }
                        // Send the obtained bytes to the UI Activity via handler
                      //  bluetoothIn.obtainMessage(handlerState, bytes, -1, readMessage).sendToTarget();
                    } catch (IOException e) {
                        break;
                    }*/
                    try {
                        StringBuilder mess = new StringBuilder("");

                        while (mmInStream.read(buffer, 0, 1) != -1) {
                            //type=buffer.

                            reception = buffer[0] & 0xff;
                            type = reception >> 5;
                            switch (type) {
                                case 0x01:
                                    data = reception & 0x1f;
                                    send = "" + data;
                                    setTheData(send, "FORWARD");
                                    reception = 0;
                                    type = 0;
                                    data = 0;
                                    break;
                                case 0x02:
                                    data = reception & 0x1f;
                                    send = "" + data;
                                    setTheData(send, "BACKWARD");
                                    reception = 0;
                                    type = 0;
                                    data = 0;
                                    break;
                                case 0x03:
                                    data = reception & 0x1f;
                                    send = "" + data;
                                    setTheData(send, "LEFT");
                                    reception = 0;
                                    type = 0;
                                    data = 0;
                                    break;
                                case 0x04:
                                    data = reception & 0x1f;
                                    send = "" + data;
                                    setTheData(send, "RIGHT");
                                    reception = 0;
                                    type = 0;
                                    data = 0;
                                    break;
                                case 0x06:
                                    data = reception & 0x1f;
                                    data = data * 10;
                                    send = "" + data;
                                    setTheData(send, "SPEED");
                                    reception = 0;
                                    type = 0;
                                    data = 0;
                                    break;
                            }


                        }

                    } catch (IOException e) {
                        break;
                    }
                }
            }


            private void setTheData(final String mess, final String text) {
                ref.runOnUiThread(new Runnable() {
                    public void run() {
                        if (text.equals("FORWARD")) {
                            TextView FW = (TextView) findViewById(R.id.forward);
                            FW.setText(mess);
                        }
                        if (text.equals("BACKWARD")) {
                            TextView BW = (TextView) findViewById(R.id.backward);
                            BW.setText(mess);
                        }
                        if (text.equals("LEFT")) {
                            TextView LEFT = (TextView) findViewById(R.id.left);
                            LEFT.setText(mess);
                        }
                        if (text.equals("RIGHT")) {
                            TextView RIGHT = (TextView) findViewById(R.id.right);
                            RIGHT.setText(mess);
                        }
                        if (text.equals("SPEED")) {
                            TextView SPEED = (TextView) findViewById(R.id.speed);
                            SPEED.setText(mess);
                        }
                    }
                });
            }


            //write method
            public void write(String input) {
                byte[] msgBuffer = input.getBytes();           //converts entered String into bytes
                try {
                    mmOutStream.write(msgBuffer);                //write bytes over BT connection via outstream
                    mmOutStream.flush();
                } catch (IOException e) {
                    //if you cannot write, close the application
                    Toast.makeText(getBaseContext(), "Connection Failure", Toast.LENGTH_LONG).show();
                }
            }


        }
    }


    //M code
    private static String deviceName = "RN-42";
    private static volatile String s = "born";
    private static String path;

    private static Controller ref;
    BluetoothAdapter mBluetoothAdapter;
    private BluetoothSocket socket = null;
    private OutputStream mmOutStream = null;
    private BTHandler bth = null;
    private boolean stop;
    private boolean stop_prev;
    private int raul;
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

        private int setTheGUI(final String mess) {
            ref.runOnUiThread(new Runnable() {
                public void run() {
                    TextView tv = (TextView) findViewById(R.id.text);
                    tv.setText(mess);
                }
            });
            Double d = Math.floor(mess.length() * 0.9);
            return d.intValue();
        }
        private void changeActivity()
        {
            ref.runOnUiThread(new Runnable() {
                public void run() {

                    Intent intent = new Intent(Controller.this, ColorBlobDetectionActivity.class);
                    startActivity(intent);

                }
            });

        }

        private void setTheButtons() {
            ref.runOnUiThread(new Runnable() {
                public void run() {
                    findViewById(R.id.forward_button).setEnabled(true);
                    findViewById(R.id.backward_button).setEnabled(true);
                    findViewById(R.id.left_button).setEnabled(true);
                    findViewById(R.id.right_button).setEnabled(true);
                    findViewById(R.id.plus_button).setEnabled(true);
                    findViewById(R.id.minus_button).setEnabled(true);
                    findViewById(R.id.m_button).setEnabled(true);
                    findViewById(R.id.park_button).setEnabled(true);
                    findViewById(R.id.stop_button).setEnabled(true);
                    findViewById(R.id.photo_button).setEnabled(true);
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
            while (true  && stop!= true) {
                try {

                    Thread.sleep(50);
                    switch (state) {
                        case "no tooth":
                            setTheGUI("I have no tooth");
                            if (bth != null) {
                                bth.socketClose();
                            }
                            break;
                        case "born":
                            delayDefault = setTheGUI("I was born");
                            BTTester btt = new BTTester();
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
                                setTheButtons();
                            } else {
                                state = "no tooth";
                            }

                            break;

                        case "The car will go forward":
                            setTheGUI("I am going forward");
                            bth.socketWrite("8");
                            state = "going forward";
                            break;
                        case "going forward":
                            setTheGUI("I am still going forward");
                            bth.socketWrite("8");
                            break;
                        case "The car will stop going forward":
                            delayDefault = setTheGUI("I am no longer going forward");
                            bth.socketWrite("5");
                            state = "";
                            break;

                        case "The car will go backward":
                            setTheGUI("I am going backward");
                            bth.socketWrite("2");
                            state = "going backward";
                            break;
                        case "going backward":
                            setTheGUI("I am still going backward");
                            bth.socketWrite("2");
                            break;
                        case "The car will stop going backward":
                            delayDefault = setTheGUI("I am no longer going backward");
                            bth.socketWrite("5");
                            state = "";
                            break;

                        case "The car will go left":
                            setTheGUI("I am going backward");
                            bth.socketWrite("4");
                            state = "going left";
                            break;
                        case "going left":
                            setTheGUI("I am still going left");
                            bth.socketWrite("4");
                            break;
                        case "The car will stop going left":
                            delayDefault = setTheGUI("I am no longer going left");
                            bth.socketWrite("5");
                            state = "";
                            break;

                        case "The car will go right":
                            setTheGUI("I am going right");
                            bth.socketWrite("6");
                            state = "going right";
                            break;
                        case "going right":
                            setTheGUI("I am still going right");
                            bth.socketWrite("6");
                            break;
                        case "The car will stop going right":
                            delayDefault = setTheGUI("I am no longer going right");
                            bth.socketWrite("5");
                            state = "";
                            break;

                        case "The speed will be increased":
                            delayDefault = setTheGUI("The speed was increased");
                            bth.socketWrite("+");
                            state = "";
                            break;

                        case "The speed will be decreased":
                            delayDefault = setTheGUI("The speed was decreased");
                            bth.socketWrite("-");
                            state = "";
                            break;

                        case "The car will stop":
                            delayDefault = setTheGUI("Braking");
                            bth.socketWrite("5");
                            i = 0;
                            state = "";
                            break;

                        case "The car will park":
                            delayDefault = setTheGUI("The car will park");
                            bth.socketWrite("9");
                            state = "";
                            break;



                        case "The path will be sent":
                            if (i != path.length()) {
                                delayDefault = setTheGUI("The path was sent: " + path);

                                command = path.charAt(i);

                                if (i != 0 && delayBreak > 0) {
                                    delayBreak--;
                                } else {

                                    switch (command) {
                                        case 'r':
                                            delayBreak = 20;
                                            bth.socketWrite("6");
                                            break;
                                        case 'l':
                                            delayBreak = 20;
                                            bth.socketWrite("4");
                                            break;
                                        case 'f':
                                            delayBreak = 20;
                                            bth.socketWrite("8");
                                            break;
                                        case 'b':
                                            delayBreak = 20;
                                            bth.socketWrite("2");
                                            break;
                                        case 's':
                                            bth.socketWrite("5");
                                            break;
                                        default:
                                            delayDefault = setTheGUI("The command was incorrect");
                                            bth.socketWrite("5");
                                            break;
                                    }
                                    i++;
                                }
                            } else {
                                if (delayDefault > 0) {
                                    delayDefault--;
                                } else {
                                    state = "The car will stop";

                                }
                            }


                            break;


                        default:
                            if (delayDefault > 0) {
                                delayDefault--;
                            } else {
                                setTheGUI("Waiting for input");

                            }


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

    public void setPath(String sequence) {
        path = sequence;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mReceiver);
        stop = true;
        if(bth.btSocket!=null) {
            //  bth.socketWrite("5");
            bth.socketClose();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        stop = false;
        raul ++;
        setContentView(R.layout.activity_control);
        ref = this;
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        Button mForwardButton = (Button) findViewById(R.id.forward_button);

        mForwardButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        processFSMState("The car will go forward");
                        return true;
                    case MotionEvent.ACTION_UP:
                        processFSMState("The car will stop going forward");
                        return true;
                }
                return false;
            }
        });
        Button mBackwardButton = (Button) findViewById(R.id.backward_button);
        mBackwardButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        processFSMState("The car will go backward");
                        return true;
                    case MotionEvent.ACTION_UP:
                        processFSMState("The car will stop going backward");
                        return true;
                }
                return false;
            }
        });

        Button mLeftButton = (Button) findViewById(R.id.left_button);
        mLeftButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        processFSMState("The car will go left");
                        return true;
                    case MotionEvent.ACTION_UP:
                        processFSMState("The car will stop going left");
                        return true;
                }
                return false;
            }
        });

        Button mRightButton = (Button) findViewById(R.id.right_button);
        mRightButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        processFSMState("The car will go right");
                        return true;
                    case MotionEvent.ACTION_UP:
                        processFSMState("The car will stop going right");
                        return true;
                }
                return false;
            }
        });

        Button mParkButton = (Button) findViewById(R.id.park_button);
        mParkButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.forward_button).setEnabled(false);
                findViewById(R.id.backward_button).setEnabled(false);
                findViewById(R.id.left_button).setEnabled(false);
                findViewById(R.id.right_button).setEnabled(false);
                findViewById(R.id.plus_button).setEnabled(false);
                findViewById(R.id.minus_button).setEnabled(false);
                findViewById(R.id.m_button).setEnabled(false);
                findViewById(R.id.park_button).setEnabled(false);
                processFSMState("The car will park");
            }
        });

        Button mMButton = (Button) findViewById(R.id.m_button);
        mMButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                processFSMState("The path will be sent");
                EditText text = (EditText) findViewById(R.id.path);
                String value = text.getText().toString();
                setPath(value);
                findViewById(R.id.forward_button).setEnabled(false);
                findViewById(R.id.backward_button).setEnabled(false);
                findViewById(R.id.left_button).setEnabled(false);
                findViewById(R.id.right_button).setEnabled(false);
                findViewById(R.id.plus_button).setEnabled(false);
                findViewById(R.id.minus_button).setEnabled(false);
                findViewById(R.id.m_button).setEnabled(false);
                findViewById(R.id.park_button).setEnabled(false);
            }
        });


        Button mPlusButton = (Button) findViewById(R.id.plus_button);
        mPlusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                processFSMState("The speed will be increased");

            }
        });

        Button mMinusButton = (Button) findViewById(R.id.minus_button);
        mMinusButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                processFSMState("The speed will be decreased");
            }
        });

        Button mStopButton = (Button) findViewById(R.id.stop_button);
        mStopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.forward_button).setEnabled(true);
                findViewById(R.id.backward_button).setEnabled(true);
                findViewById(R.id.left_button).setEnabled(true);
                findViewById(R.id.right_button).setEnabled(true);
                findViewById(R.id.plus_button).setEnabled(true);
                findViewById(R.id.minus_button).setEnabled(true);
                findViewById(R.id.m_button).setEnabled(true);
                findViewById(R.id.park_button).setEnabled(true);
                processFSMState("The car will stop");
            }
        });

        Button button = (Button) findViewById(R.id.photo_button);



        button.setOnClickListener(new View.OnClickListener() {

                                      @Override
                                      public void onClick(View view) {
                                          bth.socketClose();
                                          finish();
                                          Intent intent = new Intent(Controller.this, ColorBlobDetectionActivity.class);
                                          startActivity(intent);


                                      }
                                  }
        );

        findViewById(R.id.forward_button).setEnabled(false);
        findViewById(R.id.backward_button).setEnabled(false);
        findViewById(R.id.left_button).setEnabled(false);
        findViewById(R.id.right_button).setEnabled(false);
        findViewById(R.id.plus_button).setEnabled(false);
        findViewById(R.id.minus_button).setEnabled(false);
        findViewById(R.id.m_button).setEnabled(false);
        findViewById(R.id.park_button).setEnabled(false);
        findViewById(R.id.stop_button).setEnabled(false);
        findViewById(R.id.photo_button).setEnabled(false);
        IntentFilter filter = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
        registerReceiver(mReceiver, filter);
        t = new Thread(fsm);
        t.start();
    }


    @Override
    public void onPause() {
        super.onPause();


    }
    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
