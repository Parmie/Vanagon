using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;
using Windows.Storage.Streams;
using Windows.UI.Core;

namespace DataLogger
{
    public class ArduinoService : INotifyPropertyChanged
    {
        #region INotifyPropertyChanged

        public event PropertyChangedEventHandler PropertyChanged = delegate { };

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            if (PropertyChanged == null)
                return;

            PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion INotifyPropertyChanged

        private static ArduinoService _current;

        public static ArduinoService Current
        {
            get
            {
                if (_current == null)
                {
                    _current = new ArduinoService();
                }

                return _current;
            }
        }

        private ArduinoConfig _config;
        private SerialDevice _device;
        private Task _readTask;
        private CancellationTokenSource _cancellationTokenSource;

        public ArduinoConfig Config
        {
            get { return _config; }
            set
            {
                if (_config == value)
                    return;

                _config = value;
                OnPropertyChanged();
            }
        }

        private float _batteryLevel = 0;

        public float BatteryLevel
        {
            get { return _batteryLevel; }
            private set
            {
                //if (value == _batteryLevel)
                //    return;

                _batteryLevel = value;
                OnPropertyChanged();
            }
        }

        public void Start()
        {
            if (Config == null)
                return;

            string deviceSelector = SerialDevice.GetDeviceSelectorFromUsbVidPid(Config.VendorId, Config.ProductId);

            var deviceResult = DeviceInformation.FindAllAsync(deviceSelector).AsTask().GetAwaiter().GetResult();
            var devices = deviceResult.ToList();

            _device = SerialDevice.FromIdAsync(devices.First().Id).AsTask().GetAwaiter().GetResult();

            _cancellationTokenSource = new CancellationTokenSource();
            _readTask = Task.Run(ReadTask);
        }

        private async Task ReadTask()
        {
            using (var dataReader = new DataReader(_device.InputStream))
            {
                dataReader.InputStreamOptions = InputStreamOptions.None;

                string buffer = "";
                while (!_cancellationTokenSource.IsCancellationRequested)
                {
                    try
                    {
                        var result = await dataReader.LoadAsync(1);
                        buffer += dataReader.ReadString(result);
                        if (buffer.EndsWith("\r\n"))
                        {
                            //Debug.WriteLine(DateTime.Now.TimeOfDay.ToString() + " " + buffer.TrimEnd(new[] { '\r', '\n' }));
                            float batteryLevel;
                            if (float.TryParse(buffer.Substring(9, 4), NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign, new NumberFormatInfo { NumberDecimalSeparator = "." }, out batteryLevel))
                            {
                                await Windows.ApplicationModel.Core.CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal,
                                    () =>
                                    {
                                        BatteryLevel = batteryLevel;
                                    });
                            }

                            buffer = "";
                        }
                    }
                    catch (Exception ex)
                    {
                        buffer = "";
                    }
                }
            }
        }
    }
}