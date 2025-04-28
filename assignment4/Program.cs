// Program.cs
// Yunis Nabiyev
// CECS 342 Assignment 3
// File Type Report

using System.Xml.Linq;

namespace FileTypeReport
{
    internal static class Program
    {
        // 1. Enumerate all files in a folder recursively
        private static IEnumerable<string> EnumerateFilesRecursively(string path)
        {
            foreach (var file in System.IO.Directory.EnumerateFiles(path)) //get files in current path
            {
                yield return file.ToLower(); //return lowercased path
            }
            foreach (var dir in System.IO.Directory.EnumerateDirectories(path)) //go one level in (for each sub directory)
            {
                foreach (var file in EnumerateFilesRecursively(dir)) //get files in that directory
                {
                    yield return file.ToLower(); //return lowercased path
                }
            }
        }

        // Human readable byte size
        private static string FormatByteSize(long byteSize)
        {
            string[] sizeSuffixes = ["B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"]; //all possible size suffixes
            int suffixIndex = 0; // keeps track of which suffix to use

            var temp = (float)byteSize; //type cast the long to a float so decimal doesn't truncate
            while (temp >= 1000) //while we can go to the next size up
            {
                suffixIndex++; //go to the next suffix
                temp /= 1000; //reduce to next power
            }
            return (suffixIndex>0)? string.Format("{0:N2}", temp) + sizeSuffixes[suffixIndex] : byteSize + sizeSuffixes[suffixIndex]; //if our size is a kilobyte or more, return a rounded string with necessary suffix, otherwise return the given byteSize and "B" suffix
        }

        // Create an HTML report file
        private static XDocument CreateReport(IEnumerable<string> files)
        {

            var query = //create query
            from file in files //for each file path in collection of paths files
            group file by new FileInfo(file).Extension into fileGroup //group all alike extensions into fileGroup
            let totalSize = fileGroup.Sum(file => new FileInfo(file).Length) //calculate the size (Length) of each file in fileGroup, then sum together
            orderby totalSize descending //order groups by size in descending order
            select new //return anonymous type
            {
                Type = fileGroup.Key, // file extension of group
                Count = fileGroup.Count(), //number of files in group
                TotalSize = FormatByteSize(totalSize) //size of all files in group
            };

            var light_row_style = new XAttribute("style", "background-color:#dad2bc; color:#252323; border:3px solid #f5f1ed"); //styling for every even row
            var dark_row_style = new XAttribute("style", "background-color:#c2b6a1; color:#252323; border:3px solid #f5f1ed"); //styling for every odd row

            // 3. Functionally construct XML
            var evenOrOdd = 0;
            var tableRows =
            from fileGroup in query
            let styling = (evenOrOdd++ % 2 == 0) ? light_row_style : dark_row_style
            select
            new XElement("tr", styling, //create table row with styling
                new XElement("td", fileGroup.Type), //add group extension to row
                new XElement("td", fileGroup.Count), //add # of files in group to row
                new XElement("td", fileGroup.TotalSize) //add total size of group to row
            );

            return new XDocument( //create markup object for output
                new XElement("html", //root html element
                  new XElement("head", //root head element
                    new XElement("title", "Assignment 3 Report"), //title of page
                    new XElement("meta", new XAttribute("charset", "UTF-8")) //encoding
                  ),
                  new XElement("body", new XAttribute("style", "background-color:#a99985"), //body of page, w/ styling
                    new XElement("table", new XAttribute("style", "position:absolute; left:0px; top:0px; width:100%; text-align:center; border: solid 5px #252323; border-collapse: collapse;"), // table of info w/ styling
                      new XElement("tr", new XAttribute("style", "background-color:#70798c; color:#f5f1ed; font-size:32px; border:3px solid #f5f1ed;"), //table header w/ styling
                        new XElement("th", "Type"), //column 1: extension
                        new XElement("th", "Count"), //column 2: # of files w/ extension
                        new XElement("th", "Size") //column 3: total size of files w/ extension
                      ),
                      tableRows //add all the previously generated rows to table
                    )
                  )
                )
            );
        }

        // Console application with two arguments
        public static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.WriteLine("Usage: <program> <input folder path> <output HTML file path>");
                return;
            }

            string inputFolder = args[0];
            string outputFile = args[1];

            try
            {
                // Create the report on the recursively enumerated file paths given the folder path to start at, then save to given path
                CreateReport(EnumerateFilesRecursively(inputFolder)).Save(outputFile);

                Console.WriteLine($"Report generated successfully: {outputFile}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
        }
    }
}
