using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
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
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace DataLogger
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public static MainPage Current;

        private readonly Timer _timer;

        public ArduinoService Arduino;

        public PlotModel PlotModel { get; private set; }

        public MainPage()
        {
            Current = this;

            _timer = new Timer(OnTimerElapsed);

            PlotModel = new PlotModel { Title = "Voltage" };
            PlotModel.Axes.Add(new DateTimeAxis { Position = AxisPosition.Bottom });
            PlotModel.Axes.Add(new LinearAxis { Position = AxisPosition.Left, Minimum = 2, Maximum = 15 });

            PlotModel.Series.Add(new LineSeries { });

            Arduino = new ArduinoService();
            Arduino.Config = ArduinoConfig.Nano;
            Arduino.Start();
            Arduino.PropertyChanged += Arduino_PropertyChanged;

            _timer.Change(1000, 100);

            this.InitializeComponent();
        }

        private void Arduino_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            lock (this.PlotModel.SyncRoot)
            {
                Update(true);
            }

            this.PlotModel.InvalidatePlot(true);
        }

        private void OnTimerElapsed(object state)
        {
            lock (this.PlotModel.SyncRoot)
            {
                this.Update(false);
            }

            this.PlotModel.InvalidatePlot(true);
        }

        private void Update(bool update)
        {
            var now = DateTime.Now;
            var series = (LineSeries)PlotModel.Series[0];
            if (update)
            {
                series.Points.Add(new DataPoint(DateTimeAxis.ToDouble(now), Arduino.BatteryLevel));
            }
            
            PlotModel.Axes[0].Minimum = DateTimeAxis.ToDouble(now.AddSeconds(-5));
            PlotModel.Axes[0].Maximum = DateTimeAxis.ToDouble(now);

            PlotModel.InvalidatePlot(true);
        }
    }
}