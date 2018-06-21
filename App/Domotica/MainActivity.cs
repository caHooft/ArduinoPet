// Xamarin/C# app voor de besturing van een Arduino (Uno met Ethernet Shield) m.b.v. een socket-interface.
// Dit programma werkt samen met het Arduino-programma DomoticaServer.ino
// De besturing heeft betrekking op het aan- en uitschakelen van een Arduino pin, waar een led aan kan hangen of, 
// t.b.v. het Domotica project, een RF-zender waarmee een klik-aan-klik-uit apparaat bestuurd kan worden.
//
// De app heeft twee modes die betrekking hebben op de afhandeling van de socket-communicatie: "simple-mode" en "threaded-mode" 
// Wanneer het statement    //connector = new Connector(this);    wordt uitgecommentarieerd draait de app in "simple-mode",
// Het opvragen van gegevens van de Arduino (server) wordt dan met een Timer gerealisseerd. (De extra classes Connector.cs, 
// Receiver.cs en Sender.cs worden dan niet gebruikt.) 
// Als er een connector wordt aangemaakt draait de app in "threaded mode". De socket-communicatie wordt dan afgehandeld
// via een Sender- en een Receiver klasse, die worden aangemaakt in de Connector klasse. Deze threaded mode 
// biedt een generiekere en ook robuustere manier van communicatie, maar is ook moeilijker te begrijpen. 
// Aanbeveling: start in ieder geval met de simple-mode
//
// Werking: De communicatie met de (Arduino) server is gebaseerd op een socket-interface. Het IP- en Port-nummer
// is instelbaar. Na verbinding kunnen, middels een eenvoudig commando-protocol, opdrachten gegeven worden aan 
// de server (bijv. pin aan/uit). Indien de server om een response wordt gevraagd (bijv. led-status of een
// sensorwaarde), wordt deze in een 4-bytes ASCII-buffer ontvangen, en op het scherm geplaatst. Alle commando's naar 
// de server zijn gecodeerd met 1 char.
//
// Aanbeveling: Bestudeer het protocol in samenhang met de code van de Arduino server.
// Het default IP- en Port-nummer (zoals dat in het GUI verschijnt) kan aangepast worden in de file "Strings.xml". De
// ingestelde waarde is gebaseerd op je eigen netwerkomgeving, hier, en in de Arduino-code, is dat een router, die via DHCP
// in het segment 192.168.1.x IP-adressen uitgeeft.
// 
// Resource files:
//   Main.axml (voor het grafisch design, in de map Resources->layout)
//   Strings.xml (voor alle statische strings in het interface (ook het default IP-adres), in de map Resources->values)
// 
// De software is verder gedocumenteerd in de code. Tijdens de colleges wordt er nadere uitleg over gegeven.
// 
// Versie 1.2, 16/12/2016
// S. Oosterhaven
// W. Dalof (voor de basis van het Threaded interface)
//
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using Android.Content.PM;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using Android.Graphics;
using System.Threading.Tasks;
using System.Collections;
using MIP;

namespace Domotica
{
    [Activity(Label = "@string/application_name", MainLauncher = true, Icon = "@drawable/icon", ScreenOrientation = Android.Content.PM.ScreenOrientation.Portrait)]

    public class MainActivity : Activity
    {
        // Variables (components/controls)
        // Controls on GUI
        ToggleButton AIbutton;
        ToggleButton lightsToggle;
        Button buttonConnect;
        TextView textViewServerConnect;
        public TextView textViewChangePinStateValue, textViewSensorValue, textViewDebugValue, HumidityValueText, LDRValueText;
        EditText editTextIPAddress, editTextIPPort;
        Spinner eyesSpinner, musicSpinner;

        Socket socket = null;                       // Socket   
        Connector connector = null;                 // Connector (simple-mode or threaded-mode)
        List<Tuple<string, TextView>> commandList = new List<Tuple<string, TextView>>();  // List for commands and response places on UI
        int listIndex = 0;
        bool canContinue = true;

        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            // Set our view from the "main" layout resource (strings are loaded from Recources -> values -> Strings.xml)
            SetContentView(Resource.Layout.ConnectedApp);

            // find and set the controls, so it can be used in the code
            buttonConnect = FindViewById<Button>(Resource.Id.buttonConnect);
            textViewServerConnect = FindViewById<TextView>(Resource.Id.textViewServerConnect);
            editTextIPAddress = FindViewById<EditText>(Resource.Id.editTextIPAddress);
            editTextIPPort = FindViewById<EditText>(Resource.Id.editTextIPPort);
            eyesSpinner = FindViewById<Spinner>(Resource.Id.EyesDropdown);
            musicSpinner = FindViewById<Spinner>(Resource.Id.MusicDropdown);
            HumidityValueText = FindViewById<TextView>(Resource.Id.HumidityValue);
            LDRValueText = FindViewById<TextView>(Resource.Id.LDRDataValue);
            lightsToggle = FindViewById<ToggleButton>(Resource.Id.LightsToggle);
            AIbutton = FindViewById<ToggleButton>(Resource.Id.AIToggle);

            if(AIbutton != null)
            {
                AIbutton.Click += (o, e) => OnAIToggle(o, e);
            }
            if(lightsToggle != null)
            {
                lightsToggle.Click += (o, e) => OnLightsToggle(o, e);
            }
            if (eyesSpinner != null)
            {
                var adapter = ArrayAdapter.CreateFromResource(this, Resource.Array.eyes_values, Android.Resource.Layout.SimpleSpinnerItem);
                adapter.SetDropDownViewResource(Android.Resource.Layout.SimpleSpinnerDropDownItem);
                eyesSpinner.Adapter = adapter;
            }
            if (musicSpinner != null)
            {
                var adapter = ArrayAdapter.CreateFromResource(this, Resource.Array.music_values, Android.Resource.Layout.SimpleSpinnerItem);
                adapter.SetDropDownViewResource(Android.Resource.Layout.SimpleSpinnerDropDownItem);
                musicSpinner.Adapter = adapter;
            }

            UpdateConnectionState(4, "Disconnected");            

            //Add the "Connect" button handler.
            if (buttonConnect != null)  // if button exists
            {
                buttonConnect.Click += (sender, e) =>
                {
                    //Validate the user input (IP address and port)
                    if (CheckValidIpAddress(editTextIPAddress.Text) && CheckValidPort(editTextIPPort.Text))
                    {
                        if (connector == null) // -> simple sockets
                        {
                            ConnectSocket(editTextIPAddress.Text, editTextIPPort.Text);
                        }
                        else // -> threaded sockets
                        {
                            //Stop the thread If the Connector thread is already started.
                            if (connector.CheckStarted()) connector.StopConnector();
                               connector.StartConnector(editTextIPAddress.Text, editTextIPPort.Text);
                        }
                    }
                    else UpdateConnectionState(3, "Please check IP");
                };
            }
        }

        public void DisplayHumidityValue(string value)
        {
            HumidityValueText.Text = value;
        }

        public void DisplayLDRValue(string value)
        {
            LDRValueText.Text = value;
        }

        private void OnLightsToggle(object sender,  EventArgs args)
        {
            ToggleButton toggle = (ToggleButton)sender;
            if(toggle != null)
            {
              bool lightson = toggle.Checked;
                Toast.MakeText(this, lightson.ToString(), ToastLength.Long).Show();
            }
        }

        private void OnAIToggle(object sender, EventArgs args)
        {
            ToggleButton toggle = (ToggleButton)sender;
            if(toggle != null)
            {
                bool AIon = toggle.Checked;
                Toast.MakeText(this, AIon.ToString(), ToastLength.Long).Show();
            }
        }



        public void SendStringToArduino(string cmd, TextView text)
        {
            ResetCanContinue();
            if (connector == null) // -> simple sockets
            {
                socket.Send(Encoding.ASCII.GetBytes(cmd));                 // Send toggle-command to the Arduino
            }
            else // -> threaded sockets
            {
                if (connector.CheckStarted()) connector.SendMessage(cmd);  // Send toggle-command to the Arduino
            }

            byte[] bytes = new byte[4096]; // response is always 4 bytes
            int bytesRec = socket.Receive(bytes);
            string result = "-";
            
            result = Encoding.ASCII.GetString(bytes, 0, bytesRec);
            
            while(!result.Contains("1")&& !result.Contains("0"))
            {
                string getStatus = "GetRFStatus";
                getStatus += cmd[cmd.Length-1];
                socket.Send(Encoding.ASCII.GetBytes(getStatus));
                bytesRec = socket.Receive(bytes);
                result = Encoding.ASCII.GetString(bytes, 0, bytesRec);

                Console.WriteLine(result);
            }

            if (result.Contains("1")){
                result = "ON";
            }
            else
            {
                result = "OFF";
            }
            text.Text = result;
        }
        async void ResetCanContinue()
        {
            canContinue = false;
            await Task.Delay(500);
            canContinue = true;//start your activity here
        }


        //Send command to server and wait for response (blocking)
        //Method should only be called when socket existst
        public string ExecuteCommand(string cmd)
        {
            byte[] bytes = new byte[4096]; // response is always 4 bytes
            int bytesRec = socket.Receive(bytes);
            string result = "";
            
            if (socket != null)
            {
                //Send command to server
                socket.Send(Encoding.ASCII.GetBytes(cmd));
                result = Encoding.ASCII.GetString(bytes, 0, bytesRec);
            }
            return result;
        }

        //Update connection state label (GUI).
        public void UpdateConnectionState(int state, string text)
        {
            // connectButton
            string butConText = "Connect";  // default text
            bool butConEnabled = true;      // default state
            Color color = Color.Red;        // default color
            // pinButton
            bool butPinEnabled = false;     // default state 

            //Set "Connect" button label according to connection state.
            if (state == 1)
            {
                butConText = "Please wait";
                color = Color.Orange;
                butConEnabled = false;
            } else
            if (state == 2)
            {
                butConText = "Disconnect";
                color = Color.Green;
                butPinEnabled = true;
            }
            //Edit the control's properties on the UI thread
            RunOnUiThread(() =>
            {
                //textViewServerConnect.Text = text;
                if (butConText != null)  // text existst
                {
                    //buttonConnect.Text = butConText;
                    //textViewServerConnect.SetTextColor(color);
                    //buttonConnect.Enabled = butConEnabled;
                }
            });
        }

        //Update GUI based on Arduino response
        public void UpdateGUI(string result, TextView textview)
        {
            RunOnUiThread(() =>
            {
                if (!canContinue) return;
                if (result.Contains("OFF")) textview.SetTextColor(Color.Red);
                else if (result.Contains("ON")) textview.SetTextColor(Color.Green);
                else textview.SetTextColor(Color.White);  
                textview.Text = result;
            });
        }

        // Connect to socket ip/prt (simple sockets)
        public void ConnectSocket(string ip, string prt)
        {
            RunOnUiThread(() =>
            {
                if (socket == null)                                       // create new socket
                {
                    UpdateConnectionState(1, "Connecting...");
                    try  // to connect to the server (Arduino).
                    {
                        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                        socket.Connect(new IPEndPoint(IPAddress.Parse(ip), Convert.ToInt32(prt)));
                        if (socket.Connected)
                        {
                            UpdateConnectionState(2, "Connected");
                        }
                    } catch (Exception exception) {
                        if (socket != null)
                        {
                            socket.Close();
                            socket = null;
                        }
                        UpdateConnectionState(4, exception.Message);
                    }
	            }
                else // disconnect socket
                {
                    socket.Close(); socket = null;
                    UpdateConnectionState(4, "Disconnected");
                }
            });
        }

        //Close the connection (stop the threads) if the application stops.
        protected override void OnStop()
        {
            base.OnStop();

            if (connector != null)
            {
                if (connector.CheckStarted())
                {
                    connector.StopConnector();
                }
            }
        }

        //Close the connection (stop the threads) if the application is destroyed.
        protected override void OnDestroy()
        {
            base.OnDestroy();

            if (connector != null)
            {
                if (connector.CheckStarted())
                {
                    connector.StopConnector();
                }
            }
        }

        //Prepare the Screen's standard options menu to be displayed.
        public override bool OnPrepareOptionsMenu(IMenu menu)
        {
            //Prevent menu items from being duplicated.
            menu.Clear();

            MenuInflater.Inflate(Resource.Menu.menu, menu);
            return base.OnPrepareOptionsMenu(menu);
        }

        //Executes an action when a menu button is pressed.
        public override bool OnOptionsItemSelected(IMenuItem item)
        {
            switch (item.ItemId)
            {
                case 0:
                    //Force quit the application.
                    System.Environment.Exit(0);
                    return true;
                case 1:

                    //Stop threads forcibly (for debugging only).
                    if (connector != null)
                    {
                        if (connector.CheckStarted()) connector.Abort();
                    }
                    return true;
            }
            return base.OnOptionsItemSelected(item);
        }

        //Check if the entered IP address is valid.
        private bool CheckValidIpAddress(string ip)
        {
            if (ip != "") {
                //Check user input against regex (check if IP address is not empty).
                Regex regex = new Regex("\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b");
                Match match = regex.Match(ip);
                return match.Success;
            } else return false;
        }

        //Check if the entered port is valid.
        private bool CheckValidPort(string port)
        {
            //Check if a value is entered.
            if (port != "")
            {
                Regex regex = new Regex("[0-9]+");
                Match match = regex.Match(port);

                if (match.Success)
                {
                    int portAsInteger = Int32.Parse(port);
                    //Check if port is in range.
                    return ((portAsInteger >= 0) && (portAsInteger <= 65535));
                }
                else return false;
            } else return false;
        }
    }
}
