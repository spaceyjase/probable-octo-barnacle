using System;
using System.Threading;
using System.Threading.Tasks;

namespace Repeater
{
  public static class TaskRepeater
  {
    public static void StartNew(Action action,
          TimeSpan pollInterval,
          CancellationToken token,
          TaskCreationOptions taskCreationOptions = TaskCreationOptions.None)
    {
      Task.Factory.StartNew(
          () =>
          {
            while (true)
            {
              try
              {
                action();

                if (token.IsCancellationRequested) break;
                if (token.WaitHandle.WaitOne(pollInterval)) break;
              }
              catch
              {
                return;
              }
            }
          },
          token,
          taskCreationOptions,
          TaskScheduler.Default);
    }
  }

  public class Program
  {
    public static void Main()
    {
      var cts = new CancellationTokenSource();
      TaskRepeater.StartNew(() => Console.WriteLine("ping"), TimeSpan.FromMilliseconds(1000), cts.Token);

      Thread.Sleep(5000);

      cts.Cancel();

      Console.WriteLine("done");
    }
  }
}
