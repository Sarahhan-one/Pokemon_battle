#define DEBUG  
using CppCliWrapper;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Media;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Demon_battle
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Wrapper game;
        static private SoundPlayer player;
        public MainWindow()
        {
            InitializeComponent();
            game = new Wrapper(); 
            player = new SoundPlayer("../../../../Sound/background.wav");
            player.Play();

            //List<List<string>> paths = new List<List<string>>();
            //paths.Add(new List<string> { "../../../../Image/Pairi.png", "../../../../Image/Kkobugi.png" });
            //paths.Add(new List<string> { "../../../../Image/Naong.png", "../../../../Image/Pikachu.png" });
            //ShowImages(paths);

            // Register C# function to be called from C++
            Wrapper.RegisterImageCallback(ShowImages);
            Wrapper.RegisterAvailableCardsCallback(ShowAvailableCards);
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {

            player.Stop();
            // 게임 시작을 백그라운드 쓰레드로 실행
            Task.Run(() =>
            {
                game.StartGame(); // native C++ 게임 루프
            });
        }

        private void EndGame_Click(object sender, RoutedEventArgs e)
        {
            game.EndGame();    // C++ EndGame() 호출
        }

        public static void ShowImages(List<List<string>> paths, int playerCurrentHp, int playerMaxHp, int computerCurrentHp, int computerMaxHp, string sound_path)
        {
            // 스레드 충돌 나서 추가한 부분
            Application.Current.Dispatcher.Invoke(() =>
            {
                string a = "../../../../Sound/background.wav";
                bool ais = a == sound_path;
                player = new SoundPlayer(sound_path);
                player.Play();
                var window = (MainWindow)Application.Current.MainWindow;

                window.ImageGrid.Children.Clear();
                window.ImageGrid.RowDefinitions.Clear();
                window.ImageGrid.ColumnDefinitions.Clear();

                window.ControlPanel.Visibility = Visibility.Collapsed;
                window.GamePanel.Visibility = Visibility.Visible;

                //update HP Bars
                window.playerHpBar.Maximum = playerMaxHp;
                window.computerHpBar.Maximum = computerMaxHp;
                window.playerHpBar.Value = playerCurrentHp;
                window.computerHpBar.Value = computerCurrentHp;
                window.playerHpText.Text = $"{playerCurrentHp} / {playerMaxHp}";
                window.computerHpText.Text = $"{computerCurrentHp} / {computerMaxHp}";

                int rowCount = paths.Count;
                int colCount = paths[0].Count;

                for (int r = 0; r < rowCount; r++)
                    window.ImageGrid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(200) });

                for (int c = 0; c < colCount; c++)
                    window.ImageGrid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(200) });

                for (int r = 0; r < rowCount; r++)
                {
                    for (int c = 0; c < colCount; c++)
                    {
                        string path = paths[r][c];

                        if (string.IsNullOrWhiteSpace(path))
                        {
                            var rect = new Border
                            {
                                Background = Brushes.White,
                                BorderBrush = Brushes.Gray,
                                BorderThickness = new Thickness(1)
                            };
                            Grid.SetRow(rect, r);
                            Grid.SetColumn(rect, c);
                            window.ImageGrid.Children.Add(rect);
                        }
                        else
                        {

                            string fullPath = System.IO.Path.GetFullPath(path);
                            if (!File.Exists(path))
                            {
                                Debug.WriteLine($"[ERROR] 파일이 존재하지 않습니다: {path}");
                                continue;
                            }

                            // 이미지 불러오기 (캐시 무시)
                            var bitmap = new BitmapImage();
                            bitmap.BeginInit();
                            bitmap.CacheOption = BitmapCacheOption.OnLoad;  // 캐시 무시
                            bitmap.UriSource = new Uri(fullPath, UriKind.Absolute); 
                            bitmap.DecodePixelWidth = 100; // 또는 실제 이미지 크기나 ImageControl 크기에 맞춰 조정
                            bitmap.EndInit();

                            // 새 Image 객체 생성
                            var image = new Image
                            {
                                Source = bitmap,
                                Width = 150,
                                Height = 150,
                                Stretch = Stretch.UniformToFill,
                                HorizontalAlignment = HorizontalAlignment.Center,
                                VerticalAlignment = VerticalAlignment.Center
                            };

                            // 강제 렌더링 트릭
                            RenderOptions.SetBitmapScalingMode(image, BitmapScalingMode.HighQuality);
                            //RenderOptions.SetCachingHint(image, CachingHint.Uncache);

#if DEBUG
                            // Grid에 삽입
                            Grid.SetRow(image, r);
                            Grid.SetColumn(image, c);
                            window.ImageGrid.Children.Add(image);

                            var label = new TextBlock
                            {
                                Text = $"{r},{c}",
                                Foreground = Brushes.Red,
                                FontSize = 10,
                                VerticalAlignment = VerticalAlignment.Top,
                                HorizontalAlignment = HorizontalAlignment.Left
                            };
                            Grid.SetRow(label, r);
                            Grid.SetColumn(label, c);
                            window.ImageGrid.Children.Add(label);
#endif

                        }
                    }
                }
            });
        }
        public static void ShowAvailableCards(List<string> availableCardNames)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                var window = (MainWindow)Application.Current.MainWindow;

                window.GamePanel.Visibility = Visibility.Visible;
                window.AvailableCardsPanel.Visibility = Visibility.Visible;

                window.availableCardsList.ItemsSource = availableCardNames;
            });
        }
    }
}