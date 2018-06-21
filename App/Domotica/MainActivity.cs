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
        Server server = new Server();
        // Variables (components/controls)
        // Controls on GUI
        ToggleButton AIbutton, lightsToggle;
        TextView MIPStatusText, HumidityValueText, LDRValueText;
        Spinner eyesSpinner, musicSpinner;

        private List<KeyValuePair<string, int>> moods;
        private List<KeyValuePair<string, string>> sounds;

        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            moods = new List<KeyValuePair<string, int>>
            {
                new KeyValuePair<string, int>("Happy", 0),
                new KeyValuePair<string, int>("Sad", 1),
                new KeyValuePair<string, int>("Angry", 2),
                new KeyValuePair<string, int>("Disgusted", 3),
                new KeyValuePair<string, int>("Scared", 4)
            };

            sounds = new List<KeyValuePair<string, string>>
            {
                new KeyValuePair<string, string>("Empty", ""),
                new KeyValuePair<string, string>("Mario", "mario"),
                new KeyValuePair<string, string>("Underworld", "underworld")
            };

            // Set our view from the "main" layout resource (strings are loaded from Recources -> values -> Strings.xml)
            SetContentView(Resource.Layout.ConnectedApp);

            // find and set the controls, so it can be used in the code
            eyesSpinner = FindViewById<Spinner>(Resource.Id.EyesDropdown);
            musicSpinner = FindViewById<Spinner>(Resource.Id.MusicDropdown);
            HumidityValueText = FindViewById<TextView>(Resource.Id.HumidityValue);
            LDRValueText = FindViewById<TextView>(Resource.Id.LDRDataValue);
            MIPStatusText = FindViewById<TextView>(Resource.Id.MIPStatusValue);
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
                List<string> moodNames = new List<string>();
                foreach (var item in moods)
                    moodNames.Add(item.Key);

                var adapter = new ArrayAdapter<string>(this, Android.Resource.Layout.SimpleSpinnerItem, moodNames);
                adapter.SetDropDownViewResource(Android.Resource.Layout.SimpleSpinnerDropDownItem);
                eyesSpinner.Adapter = adapter;

                eyesSpinner.ItemSelected += (sender, args) => Mood_ItemSelected(sender, args);

            }
            if (musicSpinner != null)
            {
                List<string> soundNames = new List<string>();
                foreach (var item in sounds)
                    soundNames.Add(item.Key);

                var adapter = new ArrayAdapter<string>(this, Android.Resource.Layout.SimpleSpinnerItem, soundNames);
                adapter.SetDropDownViewResource(Android.Resource.Layout.SimpleSpinnerDropDownItem);
                musicSpinner.Adapter = adapter;

                musicSpinner.ItemSelected += (sender, args) => Music_ItemSelected(sender, args);
            }

            server.Connect(this); 
        }
        

        private void Mood_ItemSelected(object sender, AdapterView.ItemSelectedEventArgs e)
        {
            Spinner spinner = (Spinner)sender;
            string name = spinner.GetItemAtPosition(e.Position).ToString();

            string toast = string.Format("Mood  = {0}; Value = {1}",
                spinner.GetItemAtPosition(e.Position), moods[e.Position].Value);
            Toast.MakeText(this, toast, ToastLength.Long).Show();

            string sendText = "ChangeMood" + moods[e.Position].Value;
            SendStringToArduino(sendText, MIPStatusText);
        }

        private void Music_ItemSelected(object sender, AdapterView.ItemSelectedEventArgs e)
        {
            Spinner spinner = (Spinner)sender;
            string name = spinner.GetItemAtPosition(e.Position).ToString();

            string toast = string.Format("Music  = {0}; Value = {1}",
                spinner.GetItemAtPosition(e.Position), sounds[e.Position].Value);
            Toast.MakeText(this, toast, ToastLength.Long).Show();

            string sendText = "ChangeSong" + sounds[e.Position].Value + "]";
            SendStringToArduino(sendText, MIPStatusText);
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
                string sendText = "LightsToggle" + Convert.ToInt32(toggle.Checked);

                SendStringToArduino(sendText, MIPStatusText);
                Toast.MakeText(this, sendText, ToastLength.Long).Show();
            }
        }

        private void OnAIToggle(object sender, EventArgs args)
        {
            ToggleButton toggle = (ToggleButton)sender;
            if(toggle != null)
            {
                string sendText = "AIToggle" + Convert.ToInt32(toggle.Checked);

                SendStringToArduino(sendText, MIPStatusText);
                Toast.MakeText(this, sendText, ToastLength.Long).Show();
            }
        }

        public void SendStringToArduino(string cmd, TextView text)
        {
            if (!server.Send(cmd)) server.Connect(this);
            
            /*string data = server.Receive();
            if(data == "-")
            {
                Toast.MakeText(this, "No Info Received", ToastLength.Short);
            }*/
        }

        //Close the connection (stop the threads) if the application stops.
        protected override void OnStop()
        {
            base.OnStop();

            server.Stop();
        }

        //Close the connection (stop the threads) if the application is destroyed.
        protected override void OnDestroy()
        {
            base.OnDestroy();

            server.Stop();
        }

        //Prepare the Screen's standard options menu to be displayed.
        public override bool OnPrepareOptionsMenu(IMenu menu)
        {
            //Prevent menu items from being duplicated.
            menu.Clear();

            MenuInflater.Inflate(Resource.Menu.menu, menu);
            return base.OnPrepareOptionsMenu(menu);
        }
    }
}
