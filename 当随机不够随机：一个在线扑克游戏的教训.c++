今天我要讲一个发生于1999年，一个很流行的在线扑克平台的开发者开发的洗牌软件，带有很微小但很致命的漏洞的故事。
虽然这个故事已经15年了，但它给算法开发者带来的教训仍有重要意义。
在随机数产生器或算法中，很容易出现一些微小的漏洞，但这些漏洞可能会导致灾难性的结果。
在线扑克和真正的扑克一样，是以洗牌开始的。保证洗牌的随机性尤为重要。
一副正常的牌有52张，并且各不相同，这样就有52！，也就是 8.0658×10^67种不同的洗牌方式。这是一个巨大的数字。
1999年，asf软件公司发布了这个软件，支持那个年代许多流行的在线扑克平台。他们发布了洗牌算法。

算法如下， 看看能否找到不对的地方。

procedure TDeck.Shuffle;
var
    ctr: Byte;
    tmp: Byte;
 
    random_number: Byte;
begin
    { Fill the deck with unique cards }
    for ctr := 1 to 52 do
        Card[ctr] := ctr;
 
    { Generate a new seed based on the system clock }
    randomize;
 
    { Randomly rearrange each card }
    for ctr := 1 to 52 do begin
        random_number := random(51)+1;
        tmp := card[random_number];
        card[random_number] := card[ctr];
        card[ctr] := tmp;
    end;
 
    CurrentCard := 1;
    JustShuffled := True;
end;

错误1： 差一错误

上述算法试图遍历所有牌，将每一张牌跟另外一张随机选择的牌进行交换。
但是犯了每个程序员都犯过的错误——差一错误。
函数random(n)返回一个0到n-1之间的随机数，而不是程序员所想的1到n之间的。
因此，这个算法中第52张牌永远不会和他自己进行交换，也就是说第52张牌永远不会停在第52个位置。这是随机洗牌不够随机的第一个原因。

错误2：洗牌不均匀

上述算法将第i张牌和另外一张从整副也就是52张牌中随机选择的牌进行交换。
而合适的洗牌算法应该只和第i到第n张牌中的一张进行交换。这是因为考虑到每一张牌应该只进行一次随机交换。
一副牌有n!种不同的排列，合适的洗牌算法应该只产生每种排列一次。原算法使一些排列出现的概率明显高于另一些排列，是个不好的实现。

错误3：32位种子

如果你的业务或技术依赖于随机数的使用，最好的选择是采用一个硬件随机数产生器。
ASF却不是，他用了一个带有伪随机数产生器的确定机。
更糟糕的是，他使用的是32位的种子。
由于种子100%的决定了伪随机数产生器的输出，只有N^32种可能的种子值就意味着只有N^32种可能的打乱顺序。
所以在理论上有8.0658×10^67 种打乱顺序的情况下，他只有4百万可能。

错误4：系统时钟作为种子

上述算法使用Pascal函数Randomize()生成随机数，而这个函数是根据从午夜开始的毫秒数来选择种子的。
由于一天之中只有86,400,000毫秒，也就意味着上述算法只能产生86,400,000种可能的乱序。
但更糟糕的是，由于随机数产生器的种子是基于服务器时钟的，黑客们只要将他们的程序与服务器时钟同步就能够将可能出现的乱序减少到只有200,000种。
到那个时候一旦黑客知道5张牌，他就可以实时的对200,000种可能的乱序进行快速搜索，找到游戏中的那种。
所以一旦黑客知道手中的两张牌和3张公用牌，就可以猜出转牌和河牌时会来什么牌，以及其他玩家的牌。
（注：在德州扑克中，倒数第二张公共牌，叫“转牌”，最后一张牌，叫“河牌”。）

以《算法》的作者Robert Sedgewick的一段话作为结束语：

“That’s a pretty tough thing to have happen if you’re implementing online poker.
You might want to make sure that if you’re advertising that you’re doing a random shuffle that you go ahead and do so.”
—Robert Sedgewick, Professor of Computer Science, Princeton
