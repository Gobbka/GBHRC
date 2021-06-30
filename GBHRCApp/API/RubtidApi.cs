using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace GBHRCApp.API
{
    class RubtidApi
    {
        private static string get_url()
        {
            return "http://194.93.2.84:1338/";
        }

        private static HttpWebRequest new_web_request(string url,string method)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(get_url()+url);
            request.Method = method;
            request.ContentType = "application/x-www-form-urlencoded";
            request.Accept = "Accept=text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";
            return request;
        }

        public static void remove_local_token()
        {
            File.Delete(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\gbhrc\\.ini");
        }
        public static string get_local_token()
        {
            string file_path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\gbhrc\\.ini";
            if (File.Exists(file_path))
                return File.ReadAllText(file_path);
            return null;
        }

        public static void set_local_token(string token)
        {
            string file_path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\gbhrc\\.ini";

            if (!File.Exists(file_path))
                Directory.CreateDirectory(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\gbhrc");

            File.WriteAllText(file_path, token);
        }

        public static bool auth(string token,out string err)
        {
            HttpWebRequest request = new_web_request("auth", "POST");

            byte[] _byteVersion = Encoding.ASCII.GetBytes(token);

            request.ContentLength = _byteVersion.Length;

            Stream stream = request.GetRequestStream();
            stream.Write(_byteVersion, 0, _byteVersion.Length);
            stream.Close();

            HttpWebResponse response;
            try
            {
                response = (HttpWebResponse)request.GetResponse();
            }
            catch (WebException we)
            {
                response = (HttpWebResponse)we.Response;
            }

            using (StreamReader reader = new StreamReader(response.GetResponseStream()))
            {
                err = reader.ReadToEnd();
            }

            return response.StatusCode == HttpStatusCode.OK;
        }

        public static void download_dll()
        {
            using (var client = new WebClient())
            {
                client.DownloadFileCompleted += (s, e) => Console.WriteLine("Download file completed.");
                client.DownloadProgressChanged += (s, e) => Console.WriteLine($"Downloading {e.ProgressPercentage}%");
                client.DownloadFileAsync(new Uri(get_url()+"download"), "GBHRC.dll");
            }
        }

        public static double get_version()
        {
            var request = new_web_request("version", "GET");
            request.Headers["auth"] = get_local_token();

            HttpWebResponse response;

            try
            {
                response = (HttpWebResponse)request.GetResponse();
            }catch(WebException we)
            {
                response = (HttpWebResponse)we.Response;
            }

            string string_resp;
            using (StreamReader reader = new StreamReader(response.GetResponseStream()))
            {
                string_resp = reader.ReadToEnd();
                
            }

            if(response.StatusCode != HttpStatusCode.OK)
            {
                throw new Exception(string_resp);
            }

            NumberFormatInfo provider = new NumberFormatInfo();
            provider.NumberDecimalSeparator = ".";

            return Convert.ToDouble(string_resp,provider);
        }
    }
}
