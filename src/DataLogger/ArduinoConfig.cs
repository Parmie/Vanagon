using System;

namespace DataLogger
{
    public class ArduinoConfig
    {
        public static ArduinoConfig Uno => new ArduinoConfig { VendorId = 0x2A03, ProductId = 0x0043 };
        public static ArduinoConfig Nano => new ArduinoConfig { VendorId = 0x1A86, ProductId = 0x7523 };

        public ushort VendorId { get; private set; }
        public ushort ProductId { get; private set; }
    }
}