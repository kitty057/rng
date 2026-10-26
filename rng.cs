using System.Security.Cryptography;
if (args.Length == 1 && Convert.ToString(args[0]) == "help") {
    Console.WriteLine("rng [max]; replace [max] with the maximum number the program will generate, starting from 0, excluding the semicolon. if [max] is 60 it will generate a number between 0 and 60.");
}
else if (args.Length == 1 && Convert.ToInt32(args[0]) > 0) {
    int max = Convert.ToInt32(args[0])+1;
    int rand = RandomNumberGenerator.GetInt32(0, max);
    Console.WriteLine(rand);
}
